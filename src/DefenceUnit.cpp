#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

DefenceUnit::DefenceUnit()
{
    //Inicializa os atributos padrão da torre de defesa
    _health = 100;
    _currentHealth = _health;
    _armour = 5;
    _attackRange = 100;
    _meleeDamage = 0;
    _rangedDamage = 5;
    _attackDelay = 500;
    _width = 40;
    _height = 40;
    _unitType = DEFENCE;
}

int DefenceUnit::update(Unit* target)
{
    float distanceToTarget;

    distanceToTarget = sqrt(pow((_xPos - target->getXPos()), 2) + pow((_yPos - target->getYPos()), 2));

    if((int)distanceToTarget <= _attackRange){
        //Alvo está dentro do alcance da torre
        return attack(target);
    }

    return 0;
}

int DefenceUnit::attack(Unit* target)
{
    int elapsedTime;

    elapsedTime = SDL_GetTicks() - _lastAttackTime;

    if(elapsedTime >= _attackDelay){
        //Pode atacar novamente
        fprintf(stderr, "ATTACKING TARGET\n");
        _lastAttackTime = SDL_GetTicks();
        return _rangedDamage;
    }

    return 0;
}

void DefenceUnit::spawn(int screenWidth, int screenHeight)
{
	_xPos = screenWidth/2 - _width/2;
	_yPos = screenHeight/2 - _height/2;
}
