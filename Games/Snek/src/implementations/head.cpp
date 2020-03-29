#include "../headers/head.h"

#include <iostream>

int Head::move2(std::vector<Block*> body, std::vector<Block*> fruits, int& score){
    move();
    for(int i = 1; i < body.size(); i++){
        if(checkCollision(this->entity, body.at(i)->entity) == true){
            std::cout << "Game Lost\n";
            return -1;
        }
    }
    for(int i = 0; i < fruits.size(); i++){
        if(checkCollision(this->entity, fruits.at(i)->entity) == true){
            score++;
            std::cout << "Score = " << score << "\n";
            return i;
        }
    }
    return -2;
}