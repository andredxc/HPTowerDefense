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
#include <algorithm>
#include <functional>
#define FONT_TTF_FILE "../../fonts/SpectralSC-Regular.ttf"
#define SOUNDTRACK_PATH "../../soundtrack/song2.wav"

typedef struct game{
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    bool _isRunning, _audioPaused;
    int _troops;	// Bixinhos que estão ativos na rodada
    int _screenWidth, _screenHeight, _textAreaY, _textAreaHeight;
    int _bitCoins;
    int _round;
    TTF_Font* _textFont;
    SDL_Color _textColor;
    SDL_AudioDeviceID _deviceId;
    Uint8 *_wavBuffer;
    std::vector<UNIT> _soldierList;
    std::vector<UNIT> _archerList;
    std::vector<UNIT> _horsemanList;
    std::vector<PROJECTILE> _projectileList;
    UNIT _defenceUnit;
} GAME;

bool gameInitialize(GAME* game, const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
void gameHandleEvents(GAME* game);
void gameUpdate(GAME* game);
void gameRender(GAME* game);
void gameClean(GAME* game);
void gameNewRound(GAME* game);
void gameDrawStats(GAME* game);
bool gameDrawText(GAME* game, const char* text, int xPos, int yPos);
void gamePurchaseUpgrade(GAME* game, ATTRIBUTE attr);
void gameClearLists(GAME* game);
bool gameEndOfRound(GAME game);
bool gameEndOfGame(GAME game);
void gameStartNewGame(GAME* game);

#endif
