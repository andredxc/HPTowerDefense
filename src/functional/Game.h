#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "AttackUnit.h"
#include "DefenceUnit.h"
#include "Projectile.h"

#define FONT_TTF_FILE "../../fonts/SpectralSC-Regular.ttf"

typedef struct killItem{
  int _pos;
  UNIT_TYPE _type;
} KILL_ITEM;

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
    std::vector<PROJECTILE> _projectileList;
    std::vector<KILL_ITEM> _killList;
    UNIT _defenceUnit;
} GAME;

bool gameInitialize(GAME* game, const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
void gameHandleEvents(GAME* game);
void gameUpdate(GAME* game);
void gameRender(GAME* game);
void gameClean(GAME* game);
void gameNewRound(GAME* game);
void gameAddToKillList(std::vector<KILL_ITEM>* killList, int position, UNIT_TYPE unit);
void gameDrawStats(GAME* game);
bool gameDrawText(GAME* game, const char* text, int xPos, int yPos);
void gamePurchaseUpgrade(ATTRIBUTE attr);

/*
std::vector<Projectile> _projectileList;
std::vector<Archer> _archerList;
std::vector<Horseman> _horsemanList;
std::vector<Soldier> _soldierList;
std::vector<killItem> _killList;
*/

#endif
