cmake_minimum_required(VERSION 3.24)
project(infinity_chromium)

set(CMAKE_CXX_STANDARD 20)

add_executable(infinity_chromium main.cpp osx.cpp osx.h Common.cpp Common.h)
