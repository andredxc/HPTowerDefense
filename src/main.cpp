#include <stdio.h>
#include <unistd.h>
#include "Game.h"

int main(int argc, char **argv){

    Game game;
    const int fps = 60;
    const int frameDelay = 1000/fps;
    Uint32 frameStart;
    int frameTime;
    //DefenceUnit tower;
    game.initialize("HPTowerDefense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   // tower =
    while(game.getIsRunning()){

        frameStart = SDL_GetTicks();

   		if(game.getListStatus()){
            // Se todas as listas de enimigos estão vazias -> new round
	   		game.newRound();
   		}

        game.handleEvents();
        game.update();
        game.render();

        //Mantém o framerate constante em 60 fps
       frameTime = SDL_GetTicks() - frameStart;
       if(frameDelay > frameTime){
           SDL_Delay(frameDelay - frameTime);
       }
    }
    game.clean();
    return 0;
}
