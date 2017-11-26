#ifndef DEFENCE_UNIT_H
#define DEFENCE_UNIT_H
#include <stdio.h>
#include "Unit.h"

class DefenceUnit: public Unit{

protected:

public:
    DefenceUnit();
    void update(Unit* target);

protected:
    void attack(Unit* target);
    void spawn(int screenWidth, int screenHeight);
};
#endif
