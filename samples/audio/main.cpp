#include <QuickGame.hpp>

int main(int argc, char** argv){
    QuickGame::init();    
    QuickGame::Graphics::set2D();

    QuickGame::Audio::Clip clip("test.wav", false, false);
    clip.play(0);

    while(QuickGame::running()){
        QuickGame::Graphics::start_frame();
        QuickGame::Graphics::clear();

        QuickGame::Graphics::end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}