#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"

void attackSpawn(UNIT* unit, int screenWidth, int screenHeight);
int attackUpdate(UNIT* unit, UNIT* target);
void attackMove(UNIT* unit, float distanceToTower, float distance, int directionX, int directionY);
int attackAttack(UNIT* unit, UNIT* target);
UNIT createArcher();
UNIT createHorseman();
UNIT createSoldier();

#endif
