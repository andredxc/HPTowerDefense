#include "Horseman.h"
#include <SDL2/SDL_image.h>

Horseman::Horseman()
{
    _totalHealth = 40;
    _currentHealth = _totalHealth;
    _meleeDamage = 5;
    _rangedDamage = 0;
    _attackRange = 15;
    _attackDelay = 500;
    _width = 10;
    _height = 10;
    _xPos = -1;
    _yPos = -1;
    _speed = 35;
    _unitType = HORSEMAN;
    _armour = 0;
}
