#include <stdio.h>
#include <unistd.h>
#include "Game.h"

int main(int argc, char **argv){

    Game game;
    //DefenceUnit tower;
    game.initialize("HPTowerDefense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   // tower = 
    while(game.getIsRunning()){
   	
   		if(game.getListStatus()){ // Se todas as listas de enimigos estão vazias -> new round
	   		game.newRound();
   		}
        game.handleEvents();
        game.update();
        game.render();
       // sleep(2);	
    }

    game.clean();
    return 0;
}
