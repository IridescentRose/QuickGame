cmake_minimum_required(VERSION 3.17)
project(camera)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(camera main.c)

add_subdirectory(../../ QuickGame)

target_link_libraries(camera PUBLIC QuickGame)
target_include_directories(camera PUBLIC ../../include)

create_pbp_file(
    TARGET camera
    TITLE camera
    BUILD_PRX ON
)