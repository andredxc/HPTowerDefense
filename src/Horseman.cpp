#include "Horseman.h"
#include <SDL2/SDL_image.h>

Horseman::Horseman()
{
    //Determina os valores base de atributos
    _meleeDamage = 0;
    _baseHealth = 40;
    _baseArmour = 0;
    _baseRangedDamage = 5;
    _baseNumberOfTargets = 1;
    _baseAttackDelay = 500;
    _baseAttackRange = 20;
    //Determina os valores dos atributos
    _totalHealth = getAttributeValue(HEALTH, _healthLevel);
    _armour = getAttributeValue(ARMOUR, _healthLevel);
    _rangedDamage = getAttributeValue(DAMAGE, _healthLevel);
    _numberOfTargets = getAttributeValue(TARGETS, _healthLevel);
    _attackDelay = getAttributeValue(DELAY, _healthLevel);
    _attackRange = getAttributeValue(RANGE, _healthLevel);
    _currentHealth = _totalHealth;
    _reward = 30;
    _width = 10;
    _height = 10;
    _speed = 35;
    _unitType = HORSEMAN;
}
