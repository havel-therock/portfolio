#ifndef __PREDEFINED_H__
#define __PREDEFINED_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Predefined{
public:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    //Starts up SDL and creates window
    bool init();

    //Loads media
    //bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    //load media() ???? maybe not maybe in texture object or something
    // postac block do wysiwtlaenia bedzie miala pole textura?
};

#endif