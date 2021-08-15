cmake_minimum_required(VERSION 3.16)
project(Debugger)

set(CMAKE_CXX_STANDARD 20)

include_directories(ext/libelfin ext/linenoise include)

add_executable(debugger
        src/main.cpp
        src/Debugger.cpp
        src/Breakpoint.cpp
        ext/linenoise/linenoise.c)



target_include_directories(debugger
        PRIVATE
        include)