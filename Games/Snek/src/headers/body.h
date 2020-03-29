#ifndef __BODY_H__
#define __BODY_H__

#include "block.h"

class Body{

public:
    std::vector<Block*> snakeBody;
    
    Body(Block* head);
    void move();
    void grow();
    void render(SDL_Renderer* gRenderer);

    ~Body();
};

#endif