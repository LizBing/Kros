cmake_minimum_required(VERSION 3.26)
project(KrosVirtualMachine)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(${PROJECT_SOURCE_DIR})

set(ROOT ${PROJECT_SOURCE_DIR})

set(UTIL_SRC 
    ${ROOT}/util/foo.c
)

set(GC_SRC 
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(kros ${UTIL_SRC} ${GC_SRC})
