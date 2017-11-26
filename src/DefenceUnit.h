#ifndef DEFENCE_UNIT_H
#define DEFENCE_UNIT_H
#include <stdio.h>
#include "Unit.h"

class DefenceUnit: public Unit{

protected:

public:
    DefenceUnit();
    // void update(AttackUnit* attackUnit); Dar um jeito de fazer isso
	void move();
	void spawn(int screenWidth, int screenHeight);

};
#endif
