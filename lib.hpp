#pragma once

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
// Mask type
typedef unsigned int mask_t;

// Enum for Action Flag
enum action_flag_t {
  // No action
  PASS = 0,
  // Copy action
  COPY = 1,
  // Paste action
  PASTE = 2,
  // Paste to console action
  PASTE_CONSOLE = 3,
  // Cut from console action
  // !not implemented!
  CUT_CONSOLE = 4
};

// Config struct
// Stores configuration
struct Config {
  // Config file path
  static constexpr char config_path[] = "./config.json";
  // Enable multi-save?
  bool multisave{true};
  // Copy buffer file path
  std::string buffer_path{"./clipboard_data"};
  // Max number of copied entries to be stored at once
  // Removes previos one (from the begining) if limit reached
  int max_entries{10};
  // Masks for keys to be used as hotkeys
  // Mask is determined as 2^position in vector
  std::vector<uint16_t> key_masks{uiohook::VC_YEN /*1*/,
                                  uiohook::VC_CONTROL_L /*2*/,
                                  uiohook::VC_SHIFT_L /*4*/,
                                  uiohook::VC_ALT_L /*8*/,
                                  uiohook::VC_C /*16*/,
                                  uiohook::VC_V /*32*/,
                                  uiohook::VC_X /*64*/};
  // Load config
  void open();
  // Save config
  void save();
};

// Clipboard struct
// Stores copied entries
struct Clipboard {
  // Copied entries
  std::vector<std::string> contents;

  // Save clipboard to file @path
  void save(std::string const &path);
  // Load clipboard from file @path
  void open(std::string const &path);
};

namespace std {
namespace chrono {
// Unused
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

namespace uiohook {
// Fake @keys press events one by one
extern void press_keys(std::vector<uint16_t> const &keys);
// Fake @keys release events one by one
extern void release_keys(std::vector<uint16_t> const &keys);
// Fake press and then release @keys events 
extern void click_keys(std::vector<uint16_t> const &keys);
// Compare @first event with @second
extern bool operator==(uiohook_event const &first, uiohook_event const &second);
// Hook event disaptcher procedure
// Handles @event
extern void dispatch_proc(uiohook_event *const event);
} // namespace uiohook

// Load Clipboard @object from @json
extern void from_json(nlohmann::json const &json, Clipboard &object);
// Load Config @object from @json
extern void from_json(nlohmann::json const &json, Config &object);

// Mute default logger
extern bool logger(unsigned int level, const char *format, ...);

// Prepaire @str to add to Listbox
// Replace '\n' and trunc by MAX_LEN
extern std::string process_string_to_view(std::string const &str);

// Pressed keys at the moment
extern mask_t pressed_keys;
// Action flag waiting to be handled
extern action_flag_t action_flag;
// Main loop flag
// Down to stop process
extern bool main_loop;
// Maximum length of string to be displayed in Listbox
constexpr size_t MAX_LEN = 70;
// Mutex shared between main and hook loops
extern std::mutex zone_mutex;
// Condition that main loop waints to be signaled from form loop
extern std::condition_variable choice_awaiter;
// Events to be ignored (self produced) queue
extern std::queue<uiohook::uiohook_event> ignore_events;
// Config data
extern Config config;
// Clipboard stored data
extern Clipboard clipboard;
// Form pointer
// There is no need to use smart poiner but U asked for it so...
extern std::unique_ptr<nana::form> fm;
// Listbox pointer
extern std::unique_ptr<nana::listbox> lb;
// Selected text pointer
extern std::unique_ptr<std::string> selected_text;