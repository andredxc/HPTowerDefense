#ifndef DEFENCE_UNIT_H
#define DEFENCE_UNIT_H
#include <stdio.h>
#include <vector>
#include "Unit.h"
#include "Archer.h"
#include "Horseman.h"
#include "Soldier.h"
#include "Projectile.h"

class DefenceUnit: public Unit{

public:
    DefenceUnit();
    void attackClosestUnits(std::vector<Archer>* archerList, std::vector<Horseman>* horsemanList, std::vector<Soldier>* soldierList, std::vector<Projectile>* projectileList);
    int update(Unit* target);

protected:
    int attack(Unit* target);
    void spawn(int screenWidth, int screenHeight);
};
#endif
