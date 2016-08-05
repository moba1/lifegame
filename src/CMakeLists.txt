cmake_minimum_required(VERSION 2.8)

project(life)
add_executable(life life.cc cell.cc cellset.cc)
target_link_libraries(ncurses)
set(CMAKE_CXX_FLAGS "-O2 -Wall -std=c++14 -lncurses")
