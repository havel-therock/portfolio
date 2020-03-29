#include "../headers/gameLoop.h"

#include <stdio.h>
#include <string>

int main( int argc, char* args[] ){
	GameLoop game = GameLoop();
	game.start();
	return 0;
}