#include <stdio.h>
#include "AttackUnit.h"

class Soldier: public AttackUnit{

public:
    Soldier();
    virtual ~Soldier();
    void print();
};
