#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "Unit.h"

#define PROJECTILE_BMP_FILE "../../img/projectile.bmp"

typedef struct projectile{
    int _speed, _damage, _destXPos, _destYPos;
    int _width, _height, _xPos, _yPos;
    bool _isDead;
    SDL_Texture* _visualTex;
    UNIT* _target;
} PROJECTILE;

PROJECTILE createProjectile(UNIT* target, int xPos, int yPos, int attackDamage);
void deleteProjectile(PROJECTILE* proj);
void projectileUpdate(PROJECTILE* project);
void projectileMove(PROJECTILE* proj, int distanceToTarget, int distance, int directionX, int directionY);
void projectileAttack(PROJECTILE* proj, UNIT* target);
bool projectileRender(PROJECTILE* proj, SDL_Renderer* renderer, int screenWidth, int screenHeight);

#endif
