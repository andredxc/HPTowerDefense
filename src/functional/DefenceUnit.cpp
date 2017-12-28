#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

struct CloseUnit{
    int index;
    UNIT_TYPE type;
    int distance;
};

UNIT createDefenceUnit()
{
    UNIT defenceUnit;

    defenceUnit._meleeDamage = 0;
    defenceUnit._baseHealth = 100;
    defenceUnit._baseArmour = 5;
    defenceUnit._baseRangedDamage = 15;
    defenceUnit._baseNumberOfTargets = 1;
    defenceUnit._baseAttackDelay = 500;
    defenceUnit._baseAttackRange = 250;
    //Determina os valores dos atributos
    defenceUnit._totalHealth = getAttributeValue(HEALTH, defenceUnit._healthLevel);
    defenceUnit._armour = getAttributeValue(ARMOUR, defenceUnit._healthLevel);
    defenceUnit._rangedDamage = getAttributeValue(DAMAGE, defenceUnit._healthLevel);
    defenceUnit._numberOfTargets = getAttributeValue(TARGETS, defenceUnit._healthLevel);
    defenceUnit._attackDelay = getAttributeValue(DELAY, defenceUnit._healthLevel);
    defenceUnit._attackRange = getAttributeValue(RANGE, defenceUnit._healthLevel);
    defenceUnit._currentHealth = defenceUnit._totalHealth;
    defenceUnit._width = 40;
    defenceUnit._height = 40;
    defenceUnit._meleeDamage = 0;
    defenceUnit._unitType = DEFENCE;

    return defenceUnit;
}

int update(UNIT* defenceUnit, UNIT* target)
{
    float distanceToTarget;

    distanceToTarget = sqrt(pow((_xPos - target->_xPos), 2) + pow((_yPos - target->_yPos), 2));

    if((int)distanceToTarget <= defenceUnit->_attackRange){
        //Alvo está dentro do alcance da torre
        return attack(target);
    }

    return 0;
}

//TODO: Arrumar isso depois que o básico estiver funcionando
/*
void attackClosestUnits(UNIT* defenceUnit, std::vector<Archer>* archerList, std::vector<Horseman>* horsemanList, std::vector<Soldier>* soldierList, std::vector<Projectile>* projectileList)
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
*/

int attack(UNIT* defenceUnit, UNIT* target)
{
    int elapsedTime;

    elapsedTime = SDL_GetTicks() - defenceUnit->_lastAttackTime;

    if(elapsedTime >= defenceUnit->_attackDelay){
        //Pode atacar novamente
        defenceUnit->_lastAttackTime = SDL_GetTicks();
        return defenceUnit->_rangedDamage;
    }

    return 0;
}

void spawn(UNIT* defenceUnit, int screenWidth, int screenHeight)
{
	defenceUnit->_xPos = screenWidth/2 - defenceUnit->_width/2;
	defenceUnit->_yPos = screenHeight/2 - defenceUnit->_height/2;
}

void recoverHealth(UNIT* defenceUnit)
{
    defenceUnit->_currentHealth = defenceUnit->_totalHealth;
}
