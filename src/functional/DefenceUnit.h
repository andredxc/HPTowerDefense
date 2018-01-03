#ifndef DEFENCE_UNIT_H
#define DEFENCE_UNIT_H
#include <stdio.h>
#include <vector>
#include "Unit.h"
#include "Projectile.h"

// void attackClosestUnits(UNIT* defenceUnit, std::vector<Archer>* archerList, std::vector<Horseman>* horsemanList, std::vector<Soldier>* soldierList, std::vector<Projectile>* projectileList);
void attackClosestUnits(UNIT* defenceUnit, std::vector<UNIT>* archerList, std::vector<UNIT>* horsemanList, std::vector<UNIT>* soldierList, std::vector<PROJECTILE>* projectileList);
int defenceUpdate(UNIT* defenceUnit, UNIT* target);
int defenceAttack(UNIT* defenceUnit);
void defenceSpawn(int screenWidth, int screenHeight);
UNIT createDefenceUnit();

#endif
