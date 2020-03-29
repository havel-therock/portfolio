#include "../headers/eatables.h"

Eatables::Eatables(){
}

void Eatables::generateNewFruit(std::vector<Block*> snake){
    bool collide = true;
    Block* f;
    while(collide){
        collide = false;
        f = new Block(false, Block::BLOCK_SIZE + rand() % (Prep::SCREEN_WIDTH - 2 * Block::BLOCK_SIZE), Block::BLOCK_SIZE + rand() % (Prep::SCREEN_HEIGHT - 2 * Block::BLOCK_SIZE));
        for(int i = 0; i < snake.size(); i++){
            if(f->checkCollision(f->entity, snake.at(i)->entity) == true){
                collide = true;
                delete f;
                break;
            }
        }
        /*
        if(collide == false){    
            for(int i = 0; i < pears.size(); i++){
                if(f->checkCollision(f->entity, pears.at(i)->entity) == true){
                    collide = true;
                    delete f;
                    break;
                }
            }
        }*/
    }
    pears.push_back(f);    
}

void Eatables::render(SDL_Renderer* gRenderer){
    for(int i = 0; i < pears.size(); i++){
        pears.at(i)->drawBlock(gRenderer);
    }
}

void Eatables::remove(int handler){
    this->pears.erase(pears.begin() + handler);
}
