#include <stdio.h>
#include "Unit.h"

void Unit::takeDamage(uint damage){

    _health = (damage - _armour) < 0 ? (_health) : _health - (damage - _armour);
}

void Unit::setHealth(uint value){ _health = value; }
void Unit::setArmour(uint value){ _armour = value; }
void Unit::setDps(uint value){ _dps = value; }
void Unit::setRangedAttack(bool value){ _rangedAttack = value; }
void Unit::setMeleeAttack(bool value){ _meleeAttack = value; }
uint Unit::getHealth(){ return _health; }
uint Unit::getArmour(){ return _health; }
uint Unit::getDps(){ return _dps; }
bool Unit::getRangedAttack(){ return _rangedAttack; }
bool Unit::getMeleeAttack(){ return _meleeAttack; }
