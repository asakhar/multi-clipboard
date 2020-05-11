cmake_minimum_required(VERSION 3.0.0)
project(multi-clipboard VERSION 0.1.0)

include(CTest)
include(CheckIncludeFileCXX)
#include(Modules/FindLibXML++.cmake)
enable_testing()

add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)

find_package(Threads)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/_deps/uiohook-src/cmake")
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)
#include(FindLibXML++.cmake)


#set(FETCHCONTENT_BASE_DIR "./external")
#target_link_libraries(all )

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY
    https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
  clip
  GIT_REPOSITORY
    https://github.com/dacap/clip.git
  GIT_TAG origin/master
  )
FetchContent_GetProperties(clip)
if(NOT clip_POPULATED)
  FetchContent_Populate(clip)
  add_subdirectory(${clip_SOURCE_DIR} ${clip_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

target_include_directories(clip
  INTERFACE ${clip_SOURCE_DIR}
)
# In case that you have ${PNG_LIBRARY} set to support copy/paste images on Linux
#set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")

# Add clip subdirectory to compile the library
# add_subdirectory(clip)

#set(BUILD_SHARED_LIBS ON)
#FetchContent_Declare(
#  xdo
#  GIT_REPOSITORY
#    https://github.com/jordansissel/xdotool.git
#  )
#FetchContent_GetProperties(xdo)
#if(NOT xdo_POPULATED)
#  FetchContent_Populate(xdo)
  #add_subdirectory(${xdo_SOURCE_DIR} ${xdo_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()
#include_directories(${xdo_SOURCE_DIR})

#find_package(xdo)
#add_library(xdo SOURCE ${xdo_SOURCE_DIR} SHARED xdo.h)
#target_include_directories(xdo
#  INTERFACE ${xdo_SOURCE_DIR}
#)



FetchContent_Declare(
  uiohook
  GIT_REPOSITORY
    https://github.com/univrsal/libuiohook.git
    #https://github.com/kwhat/libuiohook.git
  GIT_TAG origin/cmake
  )
FetchContent_GetProperties(uiohook)
if(NOT uiohook_POPULATED)
  FetchContent_Populate(uiohook)
  add_subdirectory(${uiohook_SOURCE_DIR} ${uiohook_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


FetchContent_Declare(
  nana
  GIT_REPOSITORY
    https://github.com/cnjinhao/nana.git
  GIT_TAG origin/master
  )
FetchContent_GetProperties(nana)
if(NOT nana_POPULATED)
  FetchContent_Populate(nana)
  add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_executable(multi-clipboard main.cpp hppuiohook.hpp)
target_link_libraries(multi-clipboard PUBLIC default PRIVATE nlohmann_json::nlohmann_json PRIVATE clip PRIVATE uiohook PUBLIC nana::nana)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
