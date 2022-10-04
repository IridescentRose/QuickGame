cmake_minimum_required(VERSION 3.17)
project(audio)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(audio main.cpp)

add_subdirectory(../../ QuickGame)

target_link_libraries(audio PUBLIC QuickGame)
target_include_directories(audio PUBLIC ../../include)

create_pbp_file(
    TARGET audio
    TITLE audio
    BUILD_PRX ON
)