#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <vector>

#include "texture.h"

class Background{
public:
    Background(SDL_Renderer* gRenderer);
    std::vector<Texture*> bg;
    //render 
    //przesowanie wzgledem bohatera
    //trzymanie texturek backgroundowych
    // jedna fade in to druga texturka 
    ~Background();

};
#endif