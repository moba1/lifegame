cmake_minimum_required(VERSION 2.8)

project(life)
add_executable(life life.cc cell.cc cellset.cc)
set(CMAKE_BUILD_TYPE Release)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  target_link_libraries(life ncurses)
else()
  target_link_libraries(life ncursesw)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
