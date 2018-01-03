#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

struct CloseUnit{
    int index;
    UNIT_TYPE type;
    int distance;
};

int defenceAttack(UNIT* defenceUnit)
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

int defenceUpdate(UNIT* defenceUnit, UNIT* target)
{
    float distanceToTarget;

    distanceToTarget = sqrt(pow((defenceUnit->_xPos - target->_xPos), 2) + pow((defenceUnit->_yPos - target->_yPos), 2));

    if((int)distanceToTarget <= defenceUnit->_attackRange){
        //Alvo está dentro do alcance da torre
        return defenceAttack(defenceUnit);
    }

    return 0;
}

void attackClosestUnits(UNIT* defenceUnit, std::vector<UNIT>* archerList, std::vector<UNIT>* horsemanList, std::vector<UNIT>* soldierList, std::vector<PROJECTILE>* projectileList)
{
    int i, j, attackDamage, chosenIndex;
    std::vector<struct CloseUnit> closeUnits;
    struct CloseUnit closeUnitBuffer;

    // Preenche listas com as distâncias para cada unidade
    for(i = 0; (uint) i < archerList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = ARCHER;
        closeUnitBuffer.distance = sqrt(pow((defenceUnit->_xPos - archerList->at(i)._xPos), 2) + pow((defenceUnit->_yPos - archerList->at(i)._yPos), 2));
        closeUnits.push_back(closeUnitBuffer);
    }
    for(i = 0; (uint) i < horsemanList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = HORSEMAN;
        closeUnitBuffer.distance = sqrt(pow((defenceUnit->_xPos - horsemanList->at(i)._xPos), 2) + pow((defenceUnit->_yPos - horsemanList->at(i)._yPos), 2));
        closeUnits.push_back(closeUnitBuffer);
    }
    for(i = 0; (uint) i < soldierList->size(); i++){
        closeUnitBuffer.index = i;
        closeUnitBuffer.type = SOLDIER;
        closeUnitBuffer.distance = sqrt(pow((defenceUnit->_xPos - soldierList->at(i)._xPos), 2) + pow((defenceUnit->_yPos - soldierList->at(i)._yPos), 2));
        closeUnits.push_back(closeUnitBuffer);
    }
    // Ataca os alvos mais próximos
    for(i = 0; i < defenceUnit->_numberOfTargets; i++){
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
                attackDamage = defenceUpdate(defenceUnit, &archerList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    PROJECTILE projectileBuffer = createProjectile(&archerList->at(closeUnitBuffer.index), defenceUnit->_xPos, defenceUnit->_yPos, attackDamage);
                    projectileList->push_back(projectileBuffer);
                }
                break;
            case HORSEMAN:
                attackDamage = defenceUpdate(defenceUnit, &horsemanList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    PROJECTILE projectileBuffer = createProjectile(&horsemanList->at(closeUnitBuffer.index), defenceUnit->_xPos, defenceUnit->_yPos, attackDamage);
                    projectileList->push_back(projectileBuffer);
                }
                break;
            case SOLDIER:
                attackDamage = defenceUpdate(defenceUnit, &horsemanList->at(closeUnitBuffer.index));
                if(attackDamage > 0){
                    PROJECTILE projectileBuffer = createProjectile(&soldierList->at(closeUnitBuffer.index), defenceUnit->_xPos, defenceUnit->_yPos, attackDamage);
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

void defenceSpawn(UNIT* defenceUnit, int screenWidth, int screenHeight)
{
	defenceUnit->_xPos = screenWidth/2 - defenceUnit->_width/2;
	defenceUnit->_yPos = screenHeight/2 - defenceUnit->_height/2;
}

UNIT createDefenceUnit()
{
    UNIT defenceUnit;

    defenceUnit= createUnit();
    defenceUnit._meleeDamage = 0;
    defenceUnit._baseHealth = 100;
    defenceUnit._baseArmour = 5;
    defenceUnit._baseRangedDamage = 15;
    defenceUnit._baseNumberOfTargets = 1;
    defenceUnit._baseAttackDelay = 500;
    defenceUnit._baseAttackRange = 250;
    //Determina os valores dos atributos
    defenceUnit._totalHealth = getAttributeValue(defenceUnit, HEALTH, defenceUnit._healthLevel);
    defenceUnit._armour = getAttributeValue(defenceUnit, ARMOUR, defenceUnit._healthLevel);
    defenceUnit._rangedDamage = getAttributeValue(defenceUnit, DAMAGE, defenceUnit._healthLevel);
    defenceUnit._numberOfTargets = getAttributeValue(defenceUnit, TARGETS, defenceUnit._healthLevel);
    defenceUnit._attackDelay = getAttributeValue(defenceUnit, DELAY, defenceUnit._healthLevel);
    defenceUnit._attackRange = getAttributeValue(defenceUnit, RANGE, defenceUnit._healthLevel);
    defenceUnit._currentHealth = defenceUnit._totalHealth;
    defenceUnit._width = 40;
    defenceUnit._height = 40;
    defenceUnit._meleeDamage = 0;
    defenceUnit._unitType = DEFENCE;
    //Atribui as funções
    defenceUnit.updateFunction = defenceUpdate;
    defenceUnit.spawnFunction = defenceSpawn;
    defenceUnit.renderFunction = render;
    defenceUnit.recoverHealthFunction = recoverHealth;

    return defenceUnit;
}
