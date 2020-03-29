#include "../headers/background.h"

Background::Background(SDL_Renderer* gRenderer){
    Texture* t = new Texture();
    t->loadFromFile("res/IMG/background.png", gRenderer);
    bg.push_back(t);
}

Background::~Background(){
    bg.clear();
}