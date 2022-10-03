cmake_minimum_required(VERSION 3.17)
project(primitive)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(primitive main.c)

add_subdirectory(../../ QuickGame)

target_link_libraries(primitive PUBLIC QuickGame)
target_include_directories(primitive PUBLIC ../../include)

create_pbp_file(
    TARGET primitive
    TITLE primitive
    BUILD_PRX ON
)