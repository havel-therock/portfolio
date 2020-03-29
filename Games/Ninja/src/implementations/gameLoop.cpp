#include "../headers/gameLoop.h"

GameLoop::GameLoop(Predefined p){
	this->p = p;
}

void GameLoop::mainLoop(){
	bool quit = false;
	SDL_Event event;
	int score = 0;
	bool firstReq;

	SDL_Rect* s = new SDL_Rect();
	s->w = p.SCREEN_WIDTH;
	s->h = p.SCREEN_HEIGHT;
	s->x = 0;
	s->y = 0;

	while( !quit ){
		Background bg = Background(p.gRenderer);
		//Handle events on queue
		firstReq = true;
		while( SDL_PollEvent(&event) != 0){
			//User requests quit
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type == SDL_KEYDOWN && firstReq == true){
				//hero->handleEvent( event );
				firstReq = false;
			}
			//SDL_PumpEvents(); 
			//SDL_FlushEvent(SDL_KEYDOWN);
		}
		
		//Clear screen
		SDL_SetRenderDrawColor(p.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(p.gRenderer);
		//class that holds evry object to display 
		//class.render() thats all and before that class.move()
		bg.bg.front()->render(0, 0, NULL, s, p.gRenderer);
		//Update screen
		SDL_RenderPresent(p.gRenderer);
		SDL_Delay(50);
	}
}