#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H
#include <stdio.h>
#include "Unit.h"
#include "Projectile.h"

class AttackUnit : public Unit{

protected:
    uint _speed, _directionX, _directionY;

public:
    ~AttackUnit();
    void update(Unit* target);

protected:
    void spawn(int screenWidth, int screenHeight);
    void move(int distance, int directionX, int directionY);
    Projectile attack(Unit* target);

};
#endif
