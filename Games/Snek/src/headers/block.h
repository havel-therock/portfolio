#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <SDL2/SDL.h>

#include <vector>


class Block{
    //position
    //texture
    //rendering way
    //colision detection
    // way of moving or not

public: // Constructors
	Block(bool moveable, int xPosition, int yPosition);
    Block(bool moveable, int xPos, int yPos, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

//protected: //variables	
    bool moveable;
    Uint8 red,green,blue,alpha;
    static const int BLOCK_SIZE = 20;
    static const int BLOCK_MAX_VEL = BLOCK_SIZE; //BLOCK_SIZE/2;
    int xVelocity = 0;
    int yVelocity = 0;

//public: //variables
    enum direction {UP, DOWN, LEFT, RIGHT};
	SDL_Rect entity;
    //texture field maybe later

//public: //functions
    void handleEvent(SDL_Event& e);
    // move checks for collisions too
	void move(); 
	//void render(); draw block render but without any textures
    void drawBlock(SDL_Renderer* gRenderer);

//protected: //functions
	void setPos(int x, int y);
    bool checkCollision( SDL_Rect a, SDL_Rect b );
};

#endif