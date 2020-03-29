#ifndef __PREPARATIONS_H__
#define __PREPARATIONS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Prep{

public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    //Starts up SDL and creates window
    bool init();

    //Loads media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();
};


#endif