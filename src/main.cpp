#include "argparse.hpp"
#include "lib.hpp"

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

// void perform_paste(std::lock_guard<std::mutex> const &lock,
//                    std::vector<uint16_t> const &keys_to_press) {
//   lock.~lock_guard();
//   fm->show();
//   std::unique_lock b(zone_mutex);
//   choice_awaiter.wait(b);
//   if (selected_text) {
//     std::string check_str;
//     if (!clip::set_text(*selected_text) || !clip::get_text(check_str))
//       std::cerr << "can't set text\n";
//     else
//       uiohook::click_keys(keys_to_press);
//   }
// }

bool console_paste = 0;
bool paste_flag = 0;

void perform_paste() {
  if (selected_text) {
    std::string check_str;
    if (!clip::set_text(*selected_text) || !clip::get_text(check_str))
      std::cerr << "can't set text\n";
    else {
      if (console_paste)
        uiohook::click_keys(
            {uiohook::VC_CONTROL_L, uiohook::VC_SHIFT_L, uiohook::VC_V});
      else
        uiohook::click_keys({uiohook::VC_CONTROL_L, uiohook::VC_V});
    }
  }
}

// Main loop
// loads clipboard to Listbox;
// starts hook process async;
// checks for actions flags & performs feedback
void main_proc() {
  do {
    {
      std::unique_lock a(zone_mutex);
      if (paste_flag) {
        perform_paste();
        paste_flag = 0;
      }
      if (!pressed_keys && action_flag == action_flag_t::PASTE) {
        fm->show();
        console_paste = 0;
      }
      if (!pressed_keys && action_flag == action_flag_t::PASTE_CONSOLE) {
        fm->show();
        console_paste = 1;
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
        if (clipboard.contents.size() == config.max_entries) {
          clipboard.contents.erase(clipboard.contents.begin());
          lb->erase(lb->at(0).at(0));
        }
        clipboard.contents.push_back(board_val);
        lb->at(0).append({process_string_to_view(board_val)});
      }
#ifdef DEBUG
      if (pressed_keys)
        std::cout << "keys " << std::hex << pressed_keys << "\n";
#endif
      if (!pressed_keys)
        action_flag = action_flag_t::PASS;
    }
  } while (main_loop && !fm->visible());
  if (!main_loop)
    fm->close();
}

// Entry point
// loads config & clipboard
// starts main loop
// creates display form
int main(int argc, char *argv[]) {
  config.open();
  clipboard.open(config.buffer_path);
  argparse::Args args{argc, argv};

  if (args.option_check("--help", "-h"))
    std::cout << "help\n"; // TODO: write help
  nana::form window{};
  fm = &window;
  nana::listbox clipboard_view{window, true};
  clipboard_view.append_header("Copied text", 600);
  clipboard_view.enable_single(1, 1);
  clipboard_view.borderless(1);
  lb = &clipboard_view;

  // auto future = std::async(std::launch::async, main_proc);

  window.events().unload([](const nana::arg_unload &arg) {
    if (main_loop)
      arg.cancel = true; // this line prevents the form from closing!
    selected_text = 0;
    arg.stop_propagation();
    fm->hide();
  });
  window.events().expose([](nana::arg_expose const &arg) {
    if (!arg.exposed) {
      main_proc();
    } else {
      auto sel = lb->selected();
      if (sel.size() > 0)
        lb->at(0).at(sel[0].item).select(0);
      lb->focus();
    }
  });
  clipboard_view.events().focus([](nana::arg_focus const &arg) {
    if (!(arg.getting || lb->focused())) {
      if (selected_text)
        selected_text = 0;
      fm->hide();
    }
  });
  clipboard_view.events().selected([](nana::arg_listbox const &arg) {
    lb->focus();
    if (!arg.item.selected())
      return;
    if (selected_text)
      selected_text = 0;
    selected_text = &clipboard.contents[arg.item.pos().item];
    paste_flag = 1;
    arg.stop_propagation();
    fm->hide();
  });

  uiohook::hook_set_logger_proc(&logger);
  uiohook::hook_set_dispatch_proc(&uiohook::dispatch_proc);
  while (clipboard.contents.size() > config.max_entries)
    clipboard.contents.erase(clipboard.contents.begin());
  for (auto i : clipboard.contents)
    lb->at(0).append({process_string_to_view(i)});
  auto future = std::async(std::launch::async, uiohook::hook_run);

  window.caption("Clipboard log");
  window.size({600, 700});
  window.div("vert <><height=90% <><width=90% clipboard_view><>><>");
  window["clipboard_view"] << clipboard_view;
  window.collocate();

  main_proc();

  nana::exec();
  clipboard.save(config.buffer_path);
  config.save();
  std::cout << "Form closed. (0)\n";
  return 0;
}