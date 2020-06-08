cmake_minimum_required(VERSION 3.0.0)
project(multi-clipboard VERSION 0.1.0)

include(CTest)
include(cmake/CheckGetRepos.cmake)
include(CheckIncludeFileCXX)

# set_project_warnings(default)

# enable_testing()

add_library(default INTERFACE)
set(CMAKE_CXX_STANDARD 17)
target_compile_features(default INTERFACE cxx_std_17)

find_package(Threads)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      "${CMAKE_SOURCE_DIR}/build/_deps/uiohook-src/cmake/; ")

check_get_repos(
  nlohmann_json
  https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git v3.7.3)

check_get_repos(clip https://github.com/dacap/clip.git origin/master)
# Disable clip examples and tests
set(CLIP_EXAMPLES
    OFF
    CACHE BOOL "Compile clip examples")
set(CLIP_TESTS
    OFF
    CACHE BOOL "Compile clip tests")
target_include_directories(clip INTERFACE ${clip_SOURCE_DIR})

check_get_repos(libuiohook https://github.com/univrsal/libuiohook.git
                origin/cmake)

check_get_repos(nana https://github.com/cnjinhao/nana.git v1.7.3)

add_subdirectory(src)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME}) set(CPACK_PROJECT_VERSION
# ${PROJECT_VERSION}) include(CPack)

