cmake_minimum_required(VERSION 3.1)
project(Kros)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS 11)

set(SRC_DIR ${PROJECT_SOURCE_DIR})

include_directories(${SRC_DIR})

add_library(${PROJECT_NAME} compile_commands_trigger.cpp)
