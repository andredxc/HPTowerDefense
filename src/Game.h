#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Archer.h"
// #include "Soldier.h"
#include "Horseman.h"
#include "TroopList.h"

class Game{

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;
    bool _emptyList; // Variavel para controlar os rounds
    int _troops;	// Bixinhos que estão ativos na rodada
    int _screenWidth, _screenHeight;

public:
	// criar 3e listas -> utilizar template cada uma do tipo correspondente ao bixinho que tem tamanho maximo 100
    bool initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void newRound();
    int getIsRunning();
    int getListStatus();

	// TroopList<Archer> _archerList;
	std::vector<Archer> _archerList;
	//TroopList<Horseman> horsemanList;
    //TroopList<Soldier> soldierList;

};
#endif
