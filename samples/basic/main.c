#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;



    QuickGame_Terminate();
    return 0;
}