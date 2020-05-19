project(multi-clipboard-src)

add_executable(multi-clipboard main.cpp lib.cpp argparse.cpp)
target_link_libraries(
  multi-clipboard
  PUBLIC default
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC clip
  PUBLIC uiohook
  PUBLIC nana::nana)