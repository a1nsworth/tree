cmake_minimum_required(VERSION 3.21)
project(laba7 C)

set(CMAKE_C_STANDARD 23)

add_executable(laba7 main.c)

add_subdirectory(include)

target_link_libraries(laba7 include)
