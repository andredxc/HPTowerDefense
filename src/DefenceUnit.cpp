#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"


DefenceUnit::DefenceUnit()
{
    //Inicializa os atributos padrão da torre de defesa
    _totalHealth = 100;
    _currentHealth = _totalHealth;
    _armour = 5;
    _attackRange = 250;
    _meleeDamage = 0;
    _rangedDamage = 15;
    _attackDelay = 500;
    _width = 40;
    _height = 40;
    _unitType = DEFENCE;
    _numberOfTargets = 1;
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
    int archerIndex=0, horsemanIndex=0, soldierIndex=0;
    int i, attackDamage;
    int archerDistance, horsemanDistance, soldierDistance;  //Definido como inteiro para otimizar o trecho


    for(i = 0; i < _numberOfTargets; i++){
        //Para cada alvo que pode ser atacado ao mesmo tempo
        //Archers
        if((int)archerList->size() <= archerIndex || archerIndex < 0){
            //O índice atual não existe na lista ou ela já foi percorrida, marca a lista como finalizada
            archerIndex = -1;
            archerDistance = 100000;
        }
        else{
            //Define a distância da torre para esta unidade
            archerDistance = sqrt(pow((_xPos - archerList->at(archerIndex).getXPos()), 2) + pow((_yPos - archerList->at(archerIndex).getYPos()), 2));
        }
        //Horseman
        if((int)horsemanList->size() <= horsemanIndex || horsemanIndex < 0){
            //O índice atual não existe na lista ou ela já foi percorrida, marca a lista como finalizada
            horsemanIndex = -1;
            horsemanDistance = 100000;
        }
        else{
            //Define a distância da torre para esta unidade
            horsemanDistance = sqrt(pow((_xPos - horsemanList->at(horsemanIndex).getXPos()), 2) + pow((_yPos - horsemanList->at(horsemanIndex).getYPos()), 2));
        }
        //Soldier
        if((int)soldierList->size() <= soldierIndex || soldierIndex < 0){
            //O índice atual não existe na lista ou ela já foi percorrida, marca a lista como finalizada
            soldierIndex = -1;
            soldierDistance = 100000;
        }
        else{
            //Define a distância da torre para esta unidade
            soldierDistance = sqrt(pow((_xPos - soldierList->at(soldierIndex).getXPos()), 2) + pow((_yPos - soldierList->at(soldierIndex).getYPos()), 2));
        }
        //Define qual das unidades é a mais próxima
        if(archerIndex >= 0 && archerDistance <= horsemanDistance && archerDistance <= soldierDistance){
            //Ataca o archer e o marca como utilizado
            fprintf(stderr, "---------  TORRE ATACA ARCHER --------\n");
            attackDamage = update(&archerList->at(i));
            if(attackDamage > 0){
                Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &archerList->at(i));
                projectileList->push_back(projectileBuffer);
            }
            archerIndex++;
        }
        else if(horsemanIndex >= 0 && horsemanDistance <= archerDistance && horsemanDistance <= soldierDistance){
            //Ataca o horseman e o marca como utilizado
            fprintf(stderr, "---------  TORRE ATACA HORSEMAN --------\n");
            attackDamage = update(&horsemanList->at(i));
            if(attackDamage > 0){
                Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &horsemanList->at(i));
                projectileList->push_back(projectileBuffer);
            }
            horsemanIndex++;
        }
        else if(soldierIndex >= 0 && soldierDistance <= horsemanDistance && soldierDistance <= archerDistance){
            //Ataca o soldier e o marca como utilizado
            fprintf(stderr, "---------  TORRE ATACA SOLDIER --------\n");
            attackDamage = update(&soldierList->at(i));
            fprintf(stderr, "LAUNCHING PROJECTILE WITH %d DAMAGE\n", attackDamage);
            if(attackDamage > 0){
                Projectile projectileBuffer(2, attackDamage, 4, 4, _xPos, _yPos, &soldierList->at(i));
                projectileList->push_back(projectileBuffer);
            }
            soldierIndex++;
        }
    }
}

int DefenceUnit::attack(Unit* target)
{
    int elapsedTime;

    elapsedTime = SDL_GetTicks() - _lastAttackTime;

    if(elapsedTime >= _attackDelay){
        //Pode atacar novamente
        fprintf(stderr, "[TOWER] ATTACKING TARGET\n");
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

int DefenceUnit::getNumberOfTargets(){ return _numberOfTargets; }
