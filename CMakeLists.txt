cmake_minimum_required(VERSION 3.20)
project(RPGProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(rpg_game src/main.cc)

target_include_directories(rpg_game PRIVATE src)

set_target_properties(rpg_game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
