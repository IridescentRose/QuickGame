cmake_minimum_required(VERSION 3.17)
project(basic-contained)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(basic-contained main.c)

add_subdirectory(../../ QuickGame)

target_link_libraries(basic-contained PUBLIC QuickGame)
target_include_directories(basic-contained PUBLIC ../../include)

create_pbp_file(
    TARGET basic-contained
    TITLE basic-contained
    BUILD_PRX ON
)