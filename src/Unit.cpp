#include <stdio.h>
#include "Unit.h"

void Unit::takeDamage(uint damage){

    _health = (damage - _armour) < 0 ? (_health) : _health - (damage - _armour);
}

void Unit::setHealth(uint value){ _health = value; }
void Unit::setArmour(uint value){ _armour = value; }
void Unit::setDps(uint value){ _dps = value; }
void Unit::setRangedAttack(uint value){ _rangedAttack = value; }
void Unit::setMeleeAttack(uint value){ _meleeAttack = value; }
void Unit::setPosition(uint x, uint y){ _xPos = x; _yPos = y; }
void Unit::setAttackRange(uint value){ _attackRange = value; }
uint Unit::getHealth(){ return _health; }
uint Unit::getArmour(){ return _health; }
uint Unit::getDps(){ return _dps; }
uint Unit::getRangedAttack(){ return _rangedAttack; }
uint Unit::getMeleeAttack(){ return _meleeAttack; }
uint Unit::getXPos(){ return _xPos; }
uint Unit::getYPos(){ return _yPos; }
uint Unit::getAttackRange(){ return _attackRange; }
