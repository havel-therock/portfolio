#include "../headers/block.h"
#include "../headers/preparations.h"


Block::Block(bool mov, int xPos, int yPos){
    this->moveable = mov;
	entity = {xPos, yPos, BLOCK_SIZE, BLOCK_SIZE};
    int c1 = rand() % 256;
    int c2 = rand() % 256;
    int c3 = rand() % 256;
    while((c1 < 120) and (c2 < 130) and (c3 < 170)){
        c1 = rand() % 256;
        c2 = rand() % 256;
        c3 = rand() % 256;
    }
    
    red = c1;
    green = c2;
    blue = c3;

    alpha = 255;
}

Block::Block(bool mov, int xPos, int yPos, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    moveable = mov;
	entity = {xPos, yPos, BLOCK_SIZE, BLOCK_SIZE};
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Block::setPos(int x, int y){
	entity = {x, y, BLOCK_SIZE, BLOCK_SIZE};
}

void Block::drawBlock(SDL_Renderer* gRenderer){
	SDL_SetRenderDrawColor(gRenderer, this->red, this->green, this->blue, this->alpha);
	SDL_RenderFillRect(gRenderer, &entity);
}

void Block::handleEvent( SDL_Event& e ){
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: 
                if(xVelocity != 0){
                    yVelocity = -BLOCK_MAX_VEL; 
                    xVelocity = 0; 
                } 
                break;
            case SDLK_DOWN:
                if(xVelocity != 0){
                    yVelocity = BLOCK_MAX_VEL; 
                    xVelocity = 0; 
                }
                break;
            case SDLK_LEFT:
                if(yVelocity != 0){
                    xVelocity = -BLOCK_MAX_VEL; 
                    yVelocity = 0; 
                }
                break;
            case SDLK_RIGHT:
                if(yVelocity != 0){
                    xVelocity = BLOCK_MAX_VEL; 
                    yVelocity = 0; 
                }
                break;
            default:
                break;
        }
    }/* //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
    //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: yVelocity = 0; break;
            case SDLK_DOWN: yVelocity = 0; break;
            case SDLK_LEFT: xVelocity = 0; break;
            case SDLK_RIGHT: xVelocity = 0; break;
        }
    }*/
}

void Block::move(){
    entity.x += xVelocity;
    if(entity.x < 0){
        //Move back. Block loop movement
        //entity.x -= xVelocity;	
        entity.x = Prep::SCREEN_WIDTH - BLOCK_SIZE;
    }else if(entity.x + BLOCK_SIZE > Prep::SCREEN_WIDTH){
        //Move back. Block loop movement
        //entity.x -= xVelocity;
        entity.x = 0;
    }

    entity.y += yVelocity;
    if(entity.y < 0){
        entity.y = Prep::SCREEN_HEIGHT - BLOCK_SIZE;
        //Move back. Block way.
        //entity.y -= yVelocity;
    }else if(entity.y + BLOCK_SIZE > Prep::SCREEN_HEIGHT){
        entity.y = 0;
        //Move back. Block way.
        //entity.y -= yVelocity;
    }
}

bool Block::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}