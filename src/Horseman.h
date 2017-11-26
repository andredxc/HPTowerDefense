#ifndef HORSEMAN_H
#define HORSEMAN_H

#include <stdio.h>
#include <iostream>
#include "AttackUnit.h"

class Horseman: public AttackUnit{

public:
    Horseman();
    virtual ~Horseman();
    void print();
};
#endif
