#include <QuickGame.hpp>

int main(int argc, char** argv){
    QuickGame::init();    
    QuickGame::Graphics::set2D();

    QuickGame::Graphics::Sprite sprite({240, 136}, {256, 256}, {"circle.png", 0, 0});

    while(QuickGame::running()){
        QuickGame::Graphics::start_frame();
        QuickGame::Graphics::clear();

        sprite.draw();

        QuickGame::Graphics::end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}