#ifndef ARCHER_H
#define ARCHER_H

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
