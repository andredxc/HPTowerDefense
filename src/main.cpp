#include <stdio.h>

#include "Game.h"

int main(int argc, char **argv){

    Game game;

    game.initialize("HPTowerDefense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game.getIsRunning()){

        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}
