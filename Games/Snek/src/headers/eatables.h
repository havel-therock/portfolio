#ifndef __EATABLES_H__
#define __EATABLES_H__

#include "block.h"
#include "preparations.h"

class Eatables{

public:
    std::vector<Block*> pears;
    std::vector<Block*> snake;

    Eatables();
    
    void generateNewFruit(std::vector<Block*> snake);
    void render(SDL_Renderer* gRenderer);
    void remove(int handler);
    ~Eatables();
};

#endif