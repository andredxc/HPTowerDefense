#include <stdio.h>
#include "Unit.h"

class AttackUnit : public Unit{

protected:
    uint _speed, _directionX, _directionY;

public:
    //virtual void update() = 0;
    void move();
    void spawn(uint maxX, uint maxY);
};
 