#include "Archer.h"
#include <SDL2/SDL_image.h>

Archer::Archer()
{
    //Determina os valores base de atributos
    _meleeDamage = 0;
    _baseHealth = 20;
    _baseArmour = 0;
    _baseRangedDamage = 10;
    _baseNumberOfTargets = 1;
    _baseAttackDelay = 500;
    _baseAttackRange = 60;
    //Determina os valores dos atributos
    _totalHealth = getAttributeValue(HEALTH, _healthLevel);
    _armour = getAttributeValue(ARMOUR, _healthLevel);
    _rangedDamage = getAttributeValue(DAMAGE, _healthLevel);
    _numberOfTargets = getAttributeValue(TARGETS, _healthLevel);
    _attackDelay = getAttributeValue(DELAY, _healthLevel);
    _attackRange = getAttributeValue(RANGE, _healthLevel);
    _currentHealth = _totalHealth;
    _reward = 15;
    _width = 10;
    _height = 10;
    _speed = 25;
    _unitType = ARCHER;
    
}
