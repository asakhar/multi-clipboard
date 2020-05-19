#include "lib.hpp"

mask_t pressed_keys = 0;
action_flag_t action_flag = action_flag_t::PASS;
bool main_loop = true;

std::mutex zone_mutex;
std::condition_variable choice_awaiter;
std::queue<uiohook::uiohook_event> ignore_events;

Config config;
Clipboard clipboard;
nana::form *fm;
nana::listbox *lb;
std::string *selected_text;

namespace uiohook {
void press_keys(std::vector<uint16_t> const &keys) {
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

void release_keys(std::vector<uint16_t> const &keys) {
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

void click_keys(std::vector<uint16_t> const &keys) {
  press_keys(keys);
  release_keys(keys);
}

bool operator==(uiohook_event &a, uiohook_event &b) {
  return a.type == b.type && a.data.keyboard.keycode == b.data.keyboard.keycode;
}

void dispatch_proc(uiohook_event *const event) {
  // By the reason that hook_stop() posts event, threads lock each other
  // Ignoring this event to prevent it
  if (event->type == EVENT_HOOK_DISABLED)
    return;
  std::unique_lock a{zone_mutex};
  if (ignore_events.size() > 0 && *event == ignore_events.front()) 
    return ignore_events.pop();
  switch (event->type) {
  case EVENT_KEY_PRESSED:
#ifdef DEBUG
    std::cout << "pressed key code: (" << event->data.keyboard.keycode << ")\n";
#endif
    // Check all keys from config.key_masks & apply mask
    // for (uint16_t i = 0; i < config.key_masks.size(); ++i)
    //   if (event->data.keyboard.keycode == config.key_masks[i])
    //     pressed_keys |= 1 << i;
    pressed_keys |= config[event->data.keyboard.keycode];

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
    pressed_keys &= ~(config[event->data.keyboard.keycode]);
    if (event->data.keyboard.keycode == VC_ENTER && fm->visible() &&
        lb->at(0).size() > 0) // {
                              // if(lb->selected().size() == 0)
      lb->at(0).at(lb->at(0).size() - 1).select(1);
    //   else
    //     lb->at(0).at(lb->selected().at(0).item).select(1);
    // }
  default:
    break;
  }

  // Acction flags set up
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

void from_json(nlohmann::json const &j, Clipboard &cb) {
  cb.contents = j.get<std::vector<std::string>>();
}

void from_json(nlohmann::json const &j, std::map<uint16_t, uint64_t> &map) {
  for(auto item : j.items()) 
    map.insert_or_assign(std::stoi(item.key()), item.value().get<uint64_t>());
}

void from_json(nlohmann::json const &j, Config &config) {
  if (!j.is_object())
    std::cerr << "invalid configuration\n";
  if (j.contains("multisave"))
    j.at("multisave").get_to(config.multisave);
  if (j.contains("buffer_path"))
    j.at("buffer_path").get_to(config.buffer_path);
  if (j.contains("max_entries"))
    j.at("max_entries").get_to(config.max_entries);
  if (j.contains("masks"))
    config.key_masks = j.at("masks").get<std::map<uint16_t, uint64_t>>();
}

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

uint64_t &Config::operator[](uint16_t const &key) {
  return key_masks[key];
}

std::string &Clipboard::operator[] (size_t const &idx) {
  return contents[idx];
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
  clipboard_json.emplace("max_entries", max_entries);
  clipboard_json.emplace("masks", key_masks);
  std::fstream clipboard_f(config_path, std::ios_base::out);
  clipboard_f << clipboard_json;
  clipboard_f.close();
}

bool logger(unsigned int, const char *, ...) { return true; }

std::string process_string_to_view(std::string const &str) {
  std::stringstream ss;
  ss.str("");
  for (auto i = str.begin(); i < str.begin() + std::min(str.size(), MAX_LEN);
       ++i)
    if (*i == '\n')
      ss << "{endl}";
    else
      ss << *i;
  if (str.size() > MAX_LEN)
    ss << "...";
  return ss.str();
}

constexpr char Config::config_path[];