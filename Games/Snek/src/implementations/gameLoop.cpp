#include "../headers/gameLoop.h"
#include "../headers/head.h"
#include "../headers/eatables.h"

#include <iostream>
#include <ctime>

void GameLoop::start(){
	Prep p = Prep();
	//Start up SDL and create window
	if( !p.init() ){
		printf( "Failed to initialize!\n" );
	}else{
		// create character
		// load map in to memory if there is any?
		// load necessery 
		mainLoop(p);
	}
	p.close();
}

void GameLoop::mainLoop(Prep p){
	srand(time(NULL));
	bool quit = false;
	Head* head = new Head(true, p.SCREEN_WIDTH/2, p.SCREEN_HEIGHT/2);
	head->xVelocity = 20;
	Body* body = new Body(head);
	Eatables* fruits = new Eatables();
	fruits->generateNewFruit(body->snakeBody);
	int handler;
	SDL_Event event;
	int score = 0;
	bool firstReq;
	while( !quit ){
		//Handle events on queue
		firstReq = true;
		while( SDL_PollEvent( &event ) != 0){
			//User requests quit
			if( event.type == SDL_QUIT ){
				quit = true;
			}
			if(event.type == SDL_KEYDOWN && firstReq == true){
				head->handleEvent( event );
				firstReq = false;
			}
			//SDL_PumpEvents(); 
			//SDL_FlushEvent(SDL_KEYDOWN);
		}
		body->move();
		handler = head->move2(body->snakeBody, fruits->pears, score);
		switch(handler){
			case -1: 
			quit = true;
			SDL_Delay(1500);
			break;

			default:
			if(handler > -1){
				fruits->remove(handler);
				body->grow();
				fruits->generateNewFruit(body->snakeBody);
			}
			break;
		}
		//Clear screen
		SDL_SetRenderDrawColor( p.gRenderer, 0x00, 0x00, 0x00, 0x00 );
		SDL_RenderClear(p.gRenderer);

		
		body->render(p.gRenderer);
		fruits->render(p.gRenderer);
		//Update screen
		SDL_RenderPresent( p.gRenderer );
		SDL_Delay(50);
	}
}