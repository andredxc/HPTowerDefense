#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "Unit.h"

class Projectile{

protected:
    int _speed, _damage, _destXPos, _destYPos;
    int _width, _height, _xPos, _yPos;
    SDL_Texture* _visualTex;
    Unit* _target;

public:
    Projectile();
    Projectile(int speed, int damage, int witdh, int height, int xPos, int yPos, Unit* target);
    ~Projectile();

    void update();
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);

    Unit* getTarget();

protected:
    void move(int distanceToTarget, int distance, int directionX, int directionY);
};

#endif
