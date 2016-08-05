cmake_minimum_required(VERSION 2.8)

project(life)
add_executable(life life.cc cell.cc cellset.cc)

target_link_libraries(life ncurses)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
