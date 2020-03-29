#include "../headers/body.h"

Body::Body(Block* head){
    snakeBody.push_back(head);
}

void Body::move(){
    for(int i = snakeBody.size() - 1; i > 0; i--){
		snakeBody.at(i)->setPos(snakeBody.at(i - 1)->entity.x, snakeBody.at(i - 1)->entity.y);
	}
}

void Body::grow(){
    SDL_Rect end = snakeBody.back()->entity;
    if(snakeBody.size() < 2){
        snakeBody.push_back(new Block(true, end.x - snakeBody.back()->xVelocity, end.y - snakeBody.back()->yVelocity));
    }else{
        SDL_Rect beforeEnd = snakeBody.at(snakeBody.size() - 2)->entity;
        if(end.x > beforeEnd.x){
            snakeBody.push_back(new Block(true, end.x + end.w, end.y));
        }else if(end.x < beforeEnd.x){
            snakeBody.push_back(new Block(true, end.x - end.w, end.y));
        }else if(end.y > beforeEnd.y){
            snakeBody.push_back(new Block(true, end.x, end.y + end.h));
        }else if(end.y < beforeEnd.y){
            snakeBody.push_back(new Block(true, end.x, end.y - end.h));
        }
    }
}

void Body::render(SDL_Renderer* gRenderer){
    for(int i = 0; i < snakeBody.size(); i++){
			snakeBody.at(i)->drawBlock(gRenderer);
	}
}

Body::~Body(){

}