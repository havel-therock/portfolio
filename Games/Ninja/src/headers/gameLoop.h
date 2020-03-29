#ifndef __GAMELOOP_H__
#define __GAMELOOP_H__

#include <SDL2/SDL.h>
#include "predefined.h"
#include "background.h"



class GameLoop{
public:
    Predefined p;
    GameLoop(Predefined p);
    void mainLoop();
};

#endif