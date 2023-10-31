cmake_minimum_required(VERSION 3.27.1)

project(ToyVM VERSION 0.1)
include_directories(${PROJECT_SOURCE_DIR}/Include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(C_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-gdwarf -g3")

add_subdirectory(Source)
