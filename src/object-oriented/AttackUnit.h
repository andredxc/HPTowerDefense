#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"

class AttackUnit : public Unit{

protected:
    uint _speed, _directionX, _directionY;
    int _reward;

public:
    ~AttackUnit();
    int update(Unit* target);
    int getReward();

protected:
    void spawn(int screenWidth, int screenHeight);
    void move(float distanceToTower, float distance, int directionX, int directionY);
    int attack(Unit* target);
};
#endif
