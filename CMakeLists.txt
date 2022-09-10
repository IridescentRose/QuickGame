cmake_minimum_required(VERSION 3.17)
project(QuickGame)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE INC_FILES include/*.h)

add_library(QuickGame STATIC ${SRC_FILES} ${INC_FILES})

target_link_libraries(QuickGame PUBLIC pspgum pspgu pspge psputility pspdisplay pspctrl pspnet pspnet_apctl psppower pspaudio)
target_include_directories(QuickGame PUBLIC gu2gl/)

option(BUILD_TESTS "Build test programs" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()