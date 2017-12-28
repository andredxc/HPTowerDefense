#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Unit.h"

#define FONT_TTF_FILE "../../fonts/SpectralSC-Regular.ttf"

typedef struct game{
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning;
    bool _emptyList; // Variavel para controlar os rounds
    int _troops;	// Bixinhos que estão ativos na rodada
    int _screenWidth, _screenHeight, _textAreaY, _textAreaHeight;
    int _bitCoins;
    TTF_Font* _textFont;
    SDL_Color _textColor;
    std::vector<UNIT> _soldierList;
    std::vector<UNIT> _archerList;
    std::vector<UNIT> _horsemanList;
    //TODO: adicionar projéteis
    // std::vector<PROJECTILE> _projectileList;
    UNIT _defenceUnit;
} GAME;

typedef struct killItem{
  int _pos;
  UNIT_TYPE _type;
} KILL_ITEM;


bool gameInitialize(GAME* game, const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
void gameHandleEvents(GAME* game);
void gameUpdate();
void gameRender();
void gameClean();
void gameNewRound();
void gameAddToKillList(int position, UNIT_TYPE unit);
void gameDrawStats();
bool gameDrawText(const char* text, int xPos, int yPos);
void gamePurchaseUpgrade(ATTRIBUTE attr);

/*
std::vector<Projectile> _projectileList;
std::vector<Archer> _archerList;
std::vector<Horseman> _horsemanList;
std::vector<Soldier> _soldierList;
std::vector<killItem> _killList;
*/

#endif
