# QuickGame
Simple PSP Graphics & Games Library

## Sample

```c
#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexture_t tex = QuickGame_Texture_Load("circle.png", 0, 0);
    QGSprite_t sprite = QuickGame_Sprite_Create_Alt(240, 136, 256, 256, tex);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();

        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Sprite_Destroy(&sprite);
    QuickGame_Texture_Destroy(&tex);

    QuickGame_Terminate();
    return 0;
}
```

## Usage
QuickGame has a C, C++, and Lua-based API. These APIs all have the same features, and this includes audio, graphics, collisions, and inputs.
The goal of the API is to make PSP programming so simple you don't need to know much about the underlying system to use it.

The interpreter is available for download and the C/C++ API can be used via CMake

## Samples
Beyond just the included samples, there's also a [Pong Demo](https://youtu.be/J3xVZsjFDhw) and [Flappy Bird Demo](https://youtu.be/T5x3K4aWLMs)

## Documentation
Documentation can be found here: https://iridescentrose.github.io/QuickGame/
