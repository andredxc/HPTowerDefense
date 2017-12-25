#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

struct CloseUnit{
    int index;
    UNIT_TYPE type;
    int distance;
};

DefenceUnit::DefenceUnit()
{
    //Determina os valores base de atributos
    _meleeDamage = 0;
    _baseHealth = 100;
    _baseArmour = 5;
    _baseRangedDamage = 15;
    _baseNumberOfTargets = 1;
    _baseAttackDelay = 500;
    _baseAttackRange = 250;
    //Determina os valores dos atributos
    _totalHealth = getAttributeValue(HEALTH, _healthLevel);
    _armour = getAttributeValue(ARMOUR, _healthLevel);
    _rangedDamage = getAttributeValue(DAMAGE, _healthLevel);
    _numberOfTargets = getAttributeValue(TARGETS, _healthLevel);
    _attackDelay = getAttributeValue(DELAY, _healthLevel);
    _attackRange = getAttributeValue(RANGE, _healthLevel);
    _currentHealth = _totalHealth;
    _width = 40;
    _height = 40;
    _meleeDamage = 0;
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

void DefenceUnit::attackClosestUnits(std::vector<Archer>* archerList, std::vector<Horseman>* horsemanList, std::vector<Soldier>* soldierList, std::vector<Projectile>* projectileList)
{
    int i, j, attackDamage, chosenIndex;
    std::vector<struct CloseUnit> closeUnits;
    struct CloseUnit closeUnitBuffer;

    for(i = 0; (uint) i < archerList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = ARCHER;
        closeUnitBuffer.distance = sqrt(pow((_xPos - archerList->at(i).getXPos()), 2) + pow((_yPos - archerList->at(i).getYPos()), 2));
        closeUnits.push_back(closeUnitBuffer);
    }

    for(i = 0; (uint) i < horsemanList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = HORSEMAN;
        closeUnitBuffer.distance = sqrt(pow((_xPos - horsemanList->at(i).getXPos()), 2) + pow((_yPos - horsemanList->at(i).getYPos()), 2));
        closeUnits.push_back(closeUnitBuffer);
    }

    for(i = 0; (uint) i < soldierList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = SOLDIER;
        closeUnitBuffer.distance = sqrt(pow((_xPos - soldierList->at(i).getXPos()), 2) + pow((_yPos - soldierList->at(i).getYPos()), 2));
        closeUnits.push_back(closeUnitBuffer);
    }

    for(i = 0; i < _numberOfTargets; i++){
        for(j = 0; (uint) j < closeUnits.size(); j++){
            //Encontra a unidade mais próxima
            if(closeUnits.at(j).distance <= closeUnitBuffer.distance){
                closeUnitBuffer = closeUnits.at(j);
                chosenIndex = j;
                break;
            }
        }
        //Ataca a unidade
        switch (closeUnitBuffer.type){
            case ARCHER:
                attackDamage = update(&archerList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &archerList->at(closeUnitBuffer.index));
                    projectileList->push_back(projectileBuffer);
                }
                break;
            case HORSEMAN:
                attackDamage = update(&horsemanList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &horsemanList->at(closeUnitBuffer.index));
                    projectileList->push_back(projectileBuffer);
                }
                break;
            case SOLDIER:
                attackDamage = update(&horsemanList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &soldierList->at(closeUnitBuffer.index));
                    projectileList->push_back(projectileBuffer);
                }
                break;
            default: return;
        }
        if((uint)chosenIndex < closeUnits.size()){
            closeUnits.erase(closeUnits.begin() + chosenIndex);
        }
    }

}

int DefenceUnit::attack(Unit* target)
{
    int elapsedTime;

    elapsedTime = SDL_GetTicks() - _lastAttackTime;

    if(elapsedTime >= _attackDelay){
        //Pode atacar novamente
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

void DefenceUnit::recoverHealth()
{
    _currentHealth = _totalHealth;
}
