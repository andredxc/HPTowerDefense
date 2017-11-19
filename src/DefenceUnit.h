#ifndef X_Defence_h
#define X_Defence_h
#include <stdio.h>
#include "Unit.h"

class DefenceUnit: public Unit{

protected: 
	int _side;

public:
	void move();
	void spawn(uint maxX, uint maxY);

};
#endif