#include "Horseman.h"
#include <SDL2/SDL_image.h>

Horseman::Horseman()
{
    _reward = 30;
    _totalHealth = 40;
    _currentHealth = _totalHealth;
    _meleeDamage = 0;
    _rangedDamage = 5;
    _attackRange = 20;
    _attackDelay = 500;
    _width = 10;
    _height = 10;
    _xPos = -1;
    _yPos = -1;
    _speed = 35;
    _unitType = HORSEMAN;
    _armour = 0;
}
