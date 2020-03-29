#ifndef __GAMELOOP_H__
#define __GAMELOOP_H__

#include "preparations.h"
#include "head.h"
#include "body.h"

class GameLoop{

public:
    void start();

private:
    void mainLoop(Prep p);
};

#endif