#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"

UNIT createAttackUnit(UNIT_TYPE type);
void spawn(UNIT* unit, int screenWidth, int screenHeight);
int update(UNIT* unit, UNIT* target);
void move(UNIT* unit, float distanceToTower, float distance, int directionX, int directionY);
int attack(UNIT* unit, UNIT* target);


#endif
