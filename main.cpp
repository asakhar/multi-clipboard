#include <clip.h>
#include <condition_variable>
#include <fstream>
#include <future>
#include <iostream>
#include <mutex>
#include <nana/gui.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <vector>

extern "C" {
#ifdef _WIN32
#include <windows.h>
#endif
namespace uiohook {
#include <inttypes.h>
#include <uiohook.h>
// changing '#define' to 'constexpr' to suppress warnings and apply namespace
#include "hppuiohook.hpp"
} // namespace uiohook
}
typedef unsigned int mask_t;

enum action_flag_t {
  PASS = 0,
  COPY = 1,
  PASTE = 2,
  PASTE_CONSOLE = 3,
  CUT_CONSOLE = 4
};

struct Config {
  static constexpr char config_path[] = "./config.json";
  bool multisave{true};
  std::string buffer_path{"./clipboard_data"};
  std::vector<uint16_t> key_masks{uiohook::VC_YEN /*1*/,
                                  uiohook::VC_CONTROL_L /*2*/,
                                  uiohook::VC_SHIFT_L /*4*/,
                                  uiohook::VC_ALT_L /*8*/,
                                  uiohook::VC_C /*16*/,
                                  uiohook::VC_V /*32*/,
                                  uiohook::VC_X /*64*/};

  void open();
  void save();
};

struct Clipboard {
  std::vector<std::string> contents;

  void save(std::string const &path);
  void open(std::string const &path);
};

mask_t pressed_keys = 0;
action_flag_t action_flag = action_flag_t::PASS;
bool main_loop = true;

std::mutex zone_mutex;
std::mutex event_mutex;
std::condition_variable choice_awaiter;
std::queue<uiohook::uiohook_event> ignore_events;

Config config;
Clipboard clipboard;
std::unique_ptr<nana::form> fm;
std::unique_ptr<nana::listbox> lb;
std::unique_ptr<std::string> choosen_text;

namespace std {
namespace chrono {
template <typename _Duration> struct Timer {
  high_resolution_clock _clock;
  _V2::system_clock::time_point _start; // milli
  _Duration _delay;

  template <typename _P>
  Timer(_P delay) : _clock{}, _start{_clock.now()}, _delay{delay} {}

  bool tick() {
    if (duration_cast<_Duration>(_clock.now() - _start) > _delay) {
      _start = _clock.now();
      return 1;
    }
    return 0;
  }
};
} // namespace chrono
} // namespace std

extern "C" {
namespace uiohook {
void press_keys(std::vector<uint16_t> keys) {
  // Virtual event
  uiohook_event event;
  event.mask = 0x00;
  event.data.keyboard.keychar = CHAR_UNDEFINED;
  event.type = EVENT_KEY_PRESSED;

  for (auto key : keys) {
    event.data.keyboard.keycode = key;
    ignore_events.push(event);
    hook_post_event(&event);
  }
}

void release_keys(std::vector<uint16_t> keys) {
  // Virtual event
  uiohook_event event;
  event.mask = 0x00;
  event.data.keyboard.keychar = CHAR_UNDEFINED;
  event.type = EVENT_KEY_RELEASED;

  for (auto key : keys) {
    event.data.keyboard.keycode = key;
    ignore_events.push(event);
    hook_post_event(&event);
  }
}

void click_keys(std::vector<uint16_t> keys) {
  press_keys(keys);
  release_keys(keys);
}

bool operator==(uiohook_event &a, uiohook_event &b) {
  return a.type == b.type && a.data.keyboard.keycode == b.data.keyboard.keycode;
}

void dispatch_proc(uiohook_event *const event/*, mask_t &pressed_keys,
                   std::mutex &zone_mutex, bool &main_loop,
                   action_flag_t &action_flag, Config &config*/) {
  // By the reason that hook_stop() posts event, threads lock each other
  // Ignoring this event to prevent it
  if (event->type == EVENT_HOOK_DISABLED)
    return;
  std::lock_guard<std::mutex> a(zone_mutex);
  if (ignore_events.size() > 0 && *event == ignore_events.front()) {
    ignore_events.pop();
    return;
  }
  switch (event->type) {
  case EVENT_KEY_PRESSED:

    for (uint16_t i = 0; i < config.key_masks.size(); ++i)
      if (event->data.keyboard.keycode == config.key_masks[i])
        pressed_keys |= 1 << i;

    // If the escape key is pressed, stop hook process, join threads & escape
    // main loop
    if (event->data.keyboard.keycode == VC_ESCAPE &&
        (pressed_keys == 0b00000001)) {
      main_loop = 0;
      int status = hook_stop();
      switch (status) {
      // System level errors.
      case UIOHOOK_ERROR_OUT_OF_MEMORY:
        std::cout << "\nFailed to allocate memory. (";
        break;

      case UIOHOOK_ERROR_X_RECORD_GET_CONTEXT:
        // NOTE This is the only platform specific error that occurs on
        // hook_stop().
        std::cout << "\nFailed to get XRecord context. (";
        break;
      case UIOHOOK_SUCCESS:
        // Successful stop.
        std::cout << "\nStop succeed. (";
        break;
      // Default error.
      case UIOHOOK_FAILURE:
      default:
        std::cout << "\nAn unknown hook error occurred. (";
        break;
      }

      std::cout << std::hex << status << ")\n";
    }
    break;
  case EVENT_KEY_RELEASED:
    for (uint16_t i = 0; i < config.key_masks.size(); ++i)
      if (event->data.keyboard.keycode == config.key_masks[i])
        pressed_keys &= ~(1 << i);
  default:
    break;
  }

  if (pressed_keys == 0x23)
    action_flag = action_flag_t::PASTE;
  if (pressed_keys == 0x12 || pressed_keys == 0x42 || pressed_keys == 0x16)
    action_flag = action_flag_t::COPY;
  if (pressed_keys == 0x2A)
    action_flag = action_flag_t::PASTE_CONSOLE;
  if (pressed_keys == 0x46)
    action_flag = action_flag_t::CUT_CONSOLE;
}

} // namespace uiohook
}

void from_json(nlohmann::json const &j, Clipboard &cb) {
  cb.contents = j.get<std::vector<std::string>>();
}

void from_json(nlohmann::json const &j, Config &config) {
  j.at("multisave").get_to(config.multisave);
  j.at("buffer_path").get_to(config.buffer_path);
  config.key_masks = j.at("masks").get<std::vector<uint16_t>>();
}

constexpr char Config::config_path[];

void Clipboard::save(std::string const &path) {
  nlohmann::json clipboard_json;
  clipboard_json = contents;
  std::fstream clipboard_f(path, std::ios_base::out);
  clipboard_f << clipboard_json;
  clipboard_f.close();
}

void Clipboard::open(std::string const &path) {
  std::fstream clipboard_f{path, std::ios_base::in};
  if (clipboard_f.eof() || !clipboard_f.is_open()) {
    clipboard_f.close();
    save(path);
    return;
  }
  nlohmann::json clipboard_json;
  clipboard_json.clear();
  clipboard_json = nlohmann::json::parse(clipboard_f);
  *this = clipboard_json.get<Clipboard>();
}

void Config::open() {
  std::fstream config_f(config_path, std::ios_base::in);
  if (config_f.eof() || !config_f.is_open()) {
    config_f.close();
    save();
    return;
  }
  nlohmann::json config_json;
  config_json.clear();
  config_json = nlohmann::json::parse(config_f);
  *this = config_json.get<Config>();
}

void Config::save() {
  nlohmann::json clipboard_json;
  clipboard_json.emplace("multisave", multisave);
  clipboard_json.emplace("buffer_path", buffer_path);
  clipboard_json.emplace("masks", key_masks);
  std::fstream clipboard_f(config_path, std::ios_base::out);
  clipboard_f << clipboard_json;
  clipboard_f.close();
}

namespace argparse {
struct Args {
  std::vector<std::string> argv;
  Args(int c, char **v) : argv(c) {
    for (int i = 0; i < c; ++i)
      argv[i] = v[i];
  }
  auto begin() const { return argv.begin(); }
  auto end() const { return argv.end(); }
};

// recursion bottom
bool cmd_option_check(Args const &args, std::string const &option) {
  return std::find(args.begin(), args.end(), option) != args.end();
}

template <typename... _Ty>
bool cmd_option_check(Args const &args, std::string const &option,
                      _Ty... aliases) {
  return (std::find(args.begin(), args.end(), option) != args.end()) ||
         cmd_option_check(args, aliases...);
}

std::string cmd_option_get(Args const &args, std::string const &option) {
  return *(std::find(args.begin(), args.end(), option) + 1);
}
} // namespace argparse

// mute default logger
bool logger(unsigned int level, const char *format, ...) { return true; }

// template <typename _Fy, typename... _Ty> struct Bind {
//   std::tuple<_Ty&&...> args;
//   _Fy &&func;
//   template<typename _Functor, typename... _Args>
//   Bind(_Functor&& functor, std::initializer_list<_Args> list) :
//   func{functor}, args{list} {} void call(uiohook::event_type *event) {
//     func(event, args);
//   }
//   // template<typename _Functor>
//   // Bind(_Functor &function) : func{function} {};
//   // template<typename _Functor, typename _Farg, typename... _Args>
//   // Bind(_Functor &function, _Farg first, _Args &&... binds)
//   //     : Bind{function, binds...} {

//   //     }
// };

// using namespace std::chrono_literals;

void main_proc() {
  clipboard.open(config.buffer_path);

  uiohook::hook_set_logger_proc(&logger);
  uiohook::hook_set_dispatch_proc(&uiohook::dispatch_proc);
  for (auto i : clipboard.contents)
    lb->at(0).append({i});
  auto future = std::async(std::launch::async, uiohook::hook_run);
  do {
    {
      std::lock_guard a(zone_mutex);
      if (!pressed_keys && action_flag == action_flag_t::PASTE) {

        a.~lock_guard();
        fm->show();
        std::unique_lock b(zone_mutex);
        choice_awaiter.wait(b);
        if (choosen_text) {
          std::string check_str;
          if (!clip::set_text(*choosen_text) || !clip::get_text(check_str))
            std::cerr << "can't set text\n";
          else
            uiohook::click_keys({uiohook::VC_CONTROL_L, uiohook::VC_V});
        }
        action_flag = action_flag_t::PASS;
      }
      if (!pressed_keys && action_flag == action_flag_t::PASTE_CONSOLE) {
        a.~lock_guard();
        fm->show();
        std::unique_lock b(zone_mutex);
        choice_awaiter.wait(b);
        if (choosen_text) {
          std::string check_str;
          if (!clip::set_text(*choosen_text) || !clip::get_text(check_str))
            std::cerr << "can't set text\n";
          else
            uiohook::click_keys(
                {uiohook::VC_CONTROL_L, uiohook::VC_SHIFT_L, uiohook::VC_V});
        }
        action_flag = action_flag_t::PASS;
      }
      /*under construnction*/
      /*if (!pressed_keys && action_flag == action_flag_t::CUT_CONSOLE) {
        uiohook::click_keys(
            {uiohook::VC_CONTROL_L, uiohook::VC_SHIFT_L, uiohook::VC_C});
        std::string board_val;
        clip::get_text(board_val);
        clipboard.contents.push_back(board_val);
        if (!board_val.empty())
          for (auto i : board_val)
            if (i)
              uiohook::click_keys({uiohook::VC_BACKSPACE});
        for (auto i : clipboard.contents)
          std::cout << i << "\n";
        action_flag = action_flag_t::PASS;
      }*/
      if (!pressed_keys && action_flag == action_flag_t::COPY) {
        std::string board_val;
        clip::get_text(board_val);
        clipboard.contents.push_back(board_val);
        lb->at(0).append({board_val});
        action_flag = action_flag_t::PASS;
      }
      // if (pressed_keys)
      //   std::cout << "keys " << std::hex << pressed_keys << "\n";
      if (!pressed_keys)
        action_flag = action_flag_t::PASS;
      if (!main_loop)
        std::cout << "Thread stopped. (" << future.get() << ")\n";
    }
  } while (main_loop);
  fm->close();
  clipboard.save(config.buffer_path);
  config.save();
}

int main(int argc, char **argv) {

  config.open();
  argparse::Args args{argc, argv};

  if (argparse::cmd_option_check(args, "--help", "-h"))
    std::cout << "help\n"; // TODO: write help
  nana::form window{};
  fm.reset(&window);
  nana::listbox clipboard_view{window, true};
  clipboard_view.append_header("Copied text", 400);
  clipboard_view.enable_single(1, 1);
  clipboard_view.borderless(1);
  lb.reset(&clipboard_view);

  auto future = std::async(std::launch::async, main_proc);

  window.events().unload([](const nana::arg_unload &arg) {
    if (main_loop)
      arg.cancel = true; // this line prevents the form from closing!
    choosen_text.release();
    arg.stop_propagation();
    fm->hide();
    int timeout = 0;
    while (fm->visible() && timeout++ < 10000)
      ;
    if (timeout)
      std::cerr << "Can't hide window\n";
    timeout = 0;
    choice_awaiter.notify_one();
  });
  window.events().expose([](nana::arg_expose const &arg) {
    if (!arg.exposed)
      choice_awaiter.notify_one();
    else {
      auto sel = lb->selected();
      if (sel.size() > 0)
        lb->at(0).at(sel[0].item).select(0);
      lb->focus();
    }
  });
  clipboard_view.events().focus([](nana::arg_focus const &arg) {
    if (!(arg.getting || lb->focused())) {
      if (choosen_text)
        choosen_text.release();
      fm->hide();
      int timeout = 0;
      while (fm->visible() && timeout++ < 10000)
        ;
      if (timeout)
        std::cerr << "Can't hide window\n";
      timeout = 0;
    }
  });
  clipboard_view.events().selected([](nana::arg_listbox const &arg) {
    lb->focus();
    if (!arg.item.selected())
      return;
    if (choosen_text)
      choosen_text.release();
    choosen_text.reset(&clipboard.contents[arg.item.pos().item]);
    arg.stop_propagation();
    fm->hide();
    int timeout = 0;
    while (fm->visible() && timeout++ < 10000)
      ;
    if (timeout)
      std::cerr << "Can't hide window\n";
    timeout = 0;
  });

  window.caption("Clipboard log");
  window.size({600, 700});
  window.div("vert <><height=90% <><width=90% clipboard_view><>><>");
  window["clipboard_view"] << clipboard_view;
  window.collocate();

  nana::exec();
  lb.release();
  fm.release();
  std::cout << "Form closed. (0)\n";
  return 0;
}