#include "Archer.h"
#include <SDL2/SDL_image.h>

Archer::Archer()
{
    _health = 20;
    _meleeDamage = 0;
    _rangedDamage = 10;
    _attackRange = 60;
    _attackDelay = 500;
    _width = 10;
    _height = 10;
    _xPos = -1;
    _yPos = -1;
    _speed = 25;
    _unitType = ARCHER;
    _armour = 0;
}
