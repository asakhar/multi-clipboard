project(multi-clipboard-src)

add_executable(multi-clipboard main.cpp lib.cpp argparse.cpp)
target_compile_definitions(multi-clipboard PUBLIC DEBUG)
target_link_libraries(
  multi-clipboard
  PUBLIC default
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC clip
  PUBLIC uiohook
  PUBLIC nana::nana)
add_sanitizers(multi-clipboard)

add_executable(multi-test test.cpp lib.cpp argparse.cpp)
target_link_libraries(
  multi-test
  PUBLIC default
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC clip
  PUBLIC uiohook
  PUBLIC nana::nana
  PUBLIC Catch2::Catch2)
add_sanitizers(multi-test)
catch_discover_tests(multi-test)