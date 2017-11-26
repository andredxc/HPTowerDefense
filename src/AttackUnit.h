#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"

class AttackUnit : public Unit{

protected:
    uint _speed, _directionX, _directionY;

public:
    // void update(DefenceUnit* defenceUnit); Dar um jeito de fazer isso
    void move();
    void spawn(int screenWidth, int screenHeight);
};
#endif
