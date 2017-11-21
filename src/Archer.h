#ifndef X_Archer_h
#define X_Archer_h

#include <stdio.h>
#include <iostream>
#include "AttackUnit.h"

class Archer: public AttackUnit{

public:
    Archer();
    Archer(SDL_Renderer* renderer);
    virtual ~Archer();
    void print();
   // void update();
};
#endif
