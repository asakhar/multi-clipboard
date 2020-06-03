# Multi-clipboard [![Build Status](https://travis-ci.com/asakhar/multi-clipboard.svg?branch=master-fixed)](https://travis-ci.com/asakhar/multi-clipboard)
Multi-space clipboard

## Files:
- ### "argparse.hpp":
  #### Provides a class to handle arguments, especially commandline args
  #### Contains argparse::Args struct with following methods:
  - Checks if arguments contains @option or one of it's @aliases
  bool option_check(std::string const &option, std::string const &aliases...)

  - Returns the argument passed after @option or one of it's @aliases(first found)
  std::string option_get(std::string const &option, std::string const &aliases...) 
      
- ### "hppuiohook.hpp":
  #### Preprocessing directives to undefine c-style constants.
  #### Redefine same constants in c++ style as *constexpr auto*.
  
- ### "lib.hpp":
  #### Implements such structures as Config - container for configuration information, Clipboard - buffer for clipboard data.
  #### Contains namespace uiohook defined functions:
  - Fake @keys press events one by one
    * void press_keys(std::vector<uint16_t> const &keys);
  - Fake @keys release events one by one
    * void release_keys(std::vector<uint16_t> const &keys);
  - Fake press and then release @keys events
    * void click_keys(std::vector<uint16_t> const &keys);
  - Compare @first event with @second
    * bool operator==(uiohook_event const &first, uiohook_event const &second);
  - Hook event disaptcher procedure. Handles @event
    * void dispatch_proc(uiohook_event *const event);
    
  #### Helper function:
  - Prepaire @str to add to Listbox. Replace '\n' and trunc by MAX_LEN
    - std::string process_string_to_view(std::string const &str);
      
  #### Globals. (initialized in "lib.cpp"):
  - Pressed keys at the moment
    - mask_t pressed_keys;
  - Action flag waiting to be handled
    - action_flag_t action_flag;
  - Main loop flag. Down to stop process
    - bool main_loop;
  - Maximum length of string to be displayed in Listbox
    - constexpr size_t MAX_LEN = 70;
  - Mutex shared between main and hook loops
    - std::mutex zone_mutex;
  - Condition that main loop waints to be signaled from form loop
    - std::condition_variable choice_awaiter;
  - Events to be ignored (self produced) queue
    - std::queue<uiohook::uiohook_event> ignore_events;
  - Config data
    - Config config;
  - Clipboard stored data
    - Clipboard clipboard;
  - Form pointer. There is no need to use smart poiners because theu ought point to local variables. So i used basic ones
    - nana::form *fm;
  - Listbox pointer
    - nana::listbox *lb;
  - Selected text pointer
    - std::string *selected_text;
  
- ### "main.cpp":
  #### main_proc
    async main procedure action loop
  #### main
    entry point

## Used libraries:
  - <a href="https://github.com/dacap/clip.git">clip</a>
    * [x] <a href="https://cmake.org/cmake/help/v3.11/module/FetchContent.html">FetchContent</a>
    * Language C++
  - <a href="https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git">nlohmann json</a> 
    * [x] <a href="https://cmake.org/cmake/help/v3.11/module/FetchContent.html">FetchContent</a>
    * Language C++
  - <a href="https://github.com/univrsal/libuiohook.git">uiohook</a> 
    * [x] <a href="https://cmake.org/cmake/help/v3.11/module/FetchContent.html">FetchContent</a>
    * Language C
  - <a href="https://github.com/cnjinhao/nana.git">nana</a> 
    * [x] <a href="https://cmake.org/cmake/help/v3.11/module/FetchContent.html">FetchContent</a>
    * Language C++
  - <a>Threads</a> 
    * [ ] FetchContent
    * Language C++
  - libs dependencies
