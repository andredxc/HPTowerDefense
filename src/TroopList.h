#ifndef TROOPLIST_H
#define TROOPLIST_H

#include <iostream>
#include "Archer.h"
#include "Soldier.h"
#include "Horseman.h"

template <class TipoGenerico>

class TroopList
{

private:
    TipoGenerico* _filaptr;
    int _maxLen;
    int _fim;

public:

    TroopList();
    TroopList(int size);
    ~TroopList();
    void append(TipoGenerico number);
    void remove();
    TipoGenerico last();
    int isEmpty();
    void print();
    int size();
    TipoGenerico at(int i);
};

template class TroopList<Archer>;
template class TroopList<Horseman>;
template class TroopList<Soldier>;

#endif
