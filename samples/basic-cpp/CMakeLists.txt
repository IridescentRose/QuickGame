cmake_minimum_required(VERSION 3.17)
project(basic)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(basic main.cpp)

add_subdirectory(../../ QuickGame)

target_link_libraries(basic PUBLIC QuickGame)
target_include_directories(basic PUBLIC ../../include)

create_pbp_file(
    TARGET basic
    TITLE basic
    BUILD_PRX ON
)