cmake_minimum_required(VERSION 3.17)
project(QuickGame)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE INC_FILES include/*.h)

add_library(QuickGame STATIC ${SRC_FILES} ${INC_FILES})
add_library(STBI STATIC stbi/stb_image.h stbi/stbi.c)

target_link_libraries(QuickGame PUBLIC pspgum pspgu pspge psputility pspdisplay pspctrl pspnet pspnet_apctl psppower pspaudio STBI)

target_include_directories(QuickGame PUBLIC gu2gl/)
target_include_directories(QuickGame PUBLIC stbi/)
target_include_directories(QuickGame PUBLIC include/)

target_compile_options(QuickGame PRIVATE -Wall -Werror -Wno-unused)


add_executable(interpreter ${INC_FILES} interpreter/main.c interpreter/graphics.c interpreter/input.c interpreter/audio.c interpreter/sprite.c)

target_link_libraries(interpreter PUBLIC QuickGame pspdebug pspgum pspgu pspge psputility pspdisplay pspctrl pspnet pspnet_apctl psppower pspaudio STBI lua)
target_include_directories(interpreter PUBLIC gu2gl/)
target_include_directories(interpreter PUBLIC stbi/)
target_include_directories(interpreter PUBLIC include/)

target_compile_options(interpreter PRIVATE -Wall -Werror -Wno-unused)

create_pbp_file(
    TARGET interpreter
    TITLE QuickGameLua
    BUILD_PRX ON
)