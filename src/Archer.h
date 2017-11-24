#ifndef X_Archer_h
#define X_Archer_h

#include <stdio.h>
#include <iostream>
#include "AttackUnit.h"

class Archer: public AttackUnit{

public:
    Archer();
    virtual ~Archer();
    void print();
   // void update();
};
#endif
