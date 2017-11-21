#ifndef X_Defence_h
#define X_Defence_h
#include <stdio.h>
#include "Unit.h"

class DefenceUnit: public Unit{

protected:
	int _side;

public:
    DefenceUnit();
	void move();
	void spawn(int screenWidth, int screenHeight);

};
#endif
