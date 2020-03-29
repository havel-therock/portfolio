#include <iostream>

#include "../headers/predefined.h"
#include "../headers/gameLoop.h"

int main(int argc, char const *argv[]){
    Predefined p = Predefined();
    p.init();
    // while( not exit the game via quit or crosss symbol)
    GameLoop game = GameLoop(p);
    game.mainLoop();
    // destory gameloop
    // end of while kind of menu happens here in while 
    // maybe menu class should be called here and game loop start inside a menu 
    p.close();
    return 0;
}
