cmake_minimum_required (VERSION 3.18.4)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

project (leptjson)

add_subdirectory(obj)