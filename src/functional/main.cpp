#include <stdio.h>
#include <unistd.h>
#include "Game.h"

int main(int argc, char **argv){

    GAME game;
    const int fps = 60;
    const int frameDelay = 1000/fps;
    Uint32 frameStart;
    int frameTime;

    gameInitialize(&game, "HPTowerDefense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game._isRunning){

        frameStart = SDL_GetTicks();

        if(gameEndOfRound(game)){
            gameNewRound(&game);
        }
        gameHandleEvents(&game);
        if(!gameEndOfGame(game)){
            gameUpdate(&game);
            gameRender(&game);
        }
        //Mantém o framerate constante em 60 fps
       frameTime = SDL_GetTicks() - frameStart;
       if(frameDelay > frameTime){
           SDL_Delay(frameDelay - frameTime);
       }
    }
    gameClean(&game);
    return 0;
}
