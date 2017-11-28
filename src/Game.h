#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Archer.h"
#include "Soldier.h"
#include "Horseman.h"
#include "DefenceUnit.h"
#include "Projectile.h"

class Game{

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;
    bool _emptyList; // Variavel para controlar os rounds
    int _troops;	// Bixinhos que estão ativos na rodada
    int _screenWidth, _screenHeight;

public:
    bool initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void newRound();
    int getIsRunning();
    int getListStatus();

    struct killItem {
      int _pos;
      UNIT_TYPE _type;
    } ;

    DefenceUnit _defenceUnit;
	// TroopList<Archer> _archerList;
    std::vector<Projectile> _projectileList;
	std::vector<Archer> _archerList;
    std::vector<killItem> _killList;
	//TroopList<Horseman> horsemanList;
    //TroopList<Soldier> soldierList;

};
#endif
