#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"

class AttackUnit : public Unit{

protected:
    uint _speed, _directionX, _directionY;

public:
    ~AttackUnit();
    void update(Unit* target);

protected:
    void move(int distance, int directionX, int directionY);
    void attack(Unit* target);
    void spawn(int screenWidth, int screenHeight);

};
#endif
