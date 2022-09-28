cmake_minimum_required(VERSION 3.17)
project(collision-basic)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(collision-basic main.c)

add_subdirectory(../../ QuickGame)

target_link_libraries(collision-basic PUBLIC QuickGame)
target_include_directories(collision-basic PUBLIC ../../include)

create_pbp_file(
    TARGET collision-basic
    TITLE collision-basic
    BUILD_PRX ON
)