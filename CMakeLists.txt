cmake_minimum_required(VERSION 3.20)
project(RPGProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    src
    src/rpg
    src/rpg/lib
    src/rpg/math
)

set(SOURCES
    src/main.cc
)

add_executable(rpg_game ${SOURCES})

