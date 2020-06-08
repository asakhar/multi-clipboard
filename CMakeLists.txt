cmake_minimum_required(VERSION 3.0.0)
project(multi-clipboard VERSION 0.1.0)

include(CTest)
include(cmake/CheckGetRepos.cmake)
include(CheckIncludeFileCXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/Catch.cmake)
include(cmake/CompilerWarnings.cmake)

enable_testing()

add_library(default INTERFACE)
set_project_warnings(default)
set(CMAKE_CXX_STANDARD 17)
target_compile_features(default INTERFACE cxx_std_17)

find_package(Threads)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/_deps/libuiohook-src/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/_deps/sanitizers-cmake-src/cmake/")

set(SANITIZE_ADDRESS OFF)

set(NANA_CMAKE_FIND_BOOST_FILESYSTEM OFF)

check_get_repos(sanitizers-cmake https://github.com/arsenm/sanitizers-cmake.git
                origin/master Sanitizers)

check_get_repos(
  nlohmann_json
  https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git v3.7.3 OFF)

# Disable clip examples and tests
set(CLIP_EXAMPLES
    OFF
    CACHE BOOL "Compile clip examples")
set(CLIP_TESTS
    OFF
    CACHE BOOL "Compile clip tests")
check_get_repos(clip https://github.com/dacap/clip.git origin/master OFF)
target_include_directories(clip INTERFACE ${clip_SOURCE_DIR})

check_get_repos(libuiohook https://github.com/univrsal/libuiohook.git
                origin/cmake OFF)

check_get_repos(nana https://github.com/cnjinhao/nana.git v1.7.3 OFF)

include(CTest)

add_subdirectory(extrnal/catch2)
add_subdirectory(src)
