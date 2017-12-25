#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Archer.h"
#include "Soldier.h"
#include "Horseman.h"
#include "DefenceUnit.h"
#include "Projectile.h"

#define FONT_TTF_FILE "../../fonts/SpectralSC-Regular.ttf"

class Game{

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;
    bool _emptyList; // Variavel para controlar os rounds
    int _troops;	// Bixinhos que estão ativos na rodada
    int _screenWidth, _screenHeight, _textAreaY, _textAreaHeight;
    int _bitCoins;
    TTF_Font* _textFont;
    SDL_Color _textColor;

public:
    bool initialize(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void newRound();
    void addToKillList(int position, UNIT_TYPE unit);
    void drawStats();
    bool drawText(const char* text, int xPos, int yPos);
    void purchaseUpgrade(ATTRIBUTE attr);
    int getIsRunning();
    int getListStatus();

    struct killItem {
      int _pos;
      UNIT_TYPE _type;
    } ;

    DefenceUnit _defenceUnit;
    std::vector<Projectile> _projectileList;
	std::vector<Archer> _archerList;
	std::vector<Horseman> _horsemanList;
	std::vector<Soldier> _soldierList;
    std::vector<killItem> _killList;
    // TroopList<Archer> _archerList;
	//TroopList<Horseman> horsemanList;
    //TroopList<Soldier> soldierList;

};
#endif
