#ifndef DEFENCE_UNIT_H
#define DEFENCE_UNIT_H
#include <stdio.h>
#include <vector>
#include "Unit.h"
#include "Archer.h"
#include "Horseman.h"
#include "Soldier.h"
#include "Projectile.h"

// void attackClosestUnits(UNIT* defenceUnit, std::vector<Archer>* archerList, std::vector<Horseman>* horsemanList, std::vector<Soldier>* soldierList, std::vector<Projectile>* projectileList);
int update(UNIT* defenceUnit, UNIT* target);
void recoverHealth(UNIT* defenceUnit);
int attack(UNIT* defenceUnit, UNIT* target);
void spawn(int screenWidth, int screenHeight);

#endif
