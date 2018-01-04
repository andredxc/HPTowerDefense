#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "AttackUnit.h"

/* Inicializa a posição de uma unidade de ataque */
void attackSpawn(UNIT* unit, int screenWidth, int screenHeight)
{
    int wall;

    //Define a parede da tela
    wall = rand() % 4;
    if(wall == 0 || wall == 1){
        //Paredes verticais
        unit->_yPos = rand() % (screenHeight+1);
        //Define x de acordo com a parede da esquerda(wall==0) ou da direita(wall==1)
        //Subtrai _width pois o desenho começa pela esquerda do objeto
        unit->_xPos = (wall == 0) ? 0 : screenWidth - unit->_width;
    }
    else if(wall == 2 || wall == 3){
        //Paredes horizontais
        unit->_xPos = rand() % (screenWidth+1);
        //Define y de acordo com a parede de baixo(wall==2) ou a de cima(wall==3)
        unit->_yPos = (wall == 2) ? 0 : screenHeight - unit->_height;
    }
    else{
        printf("Erro fatal - %s\n", __FUNCTION__);
    }
}

/* Move em diração as coordenadas especificadas */
void attackMove(UNIT* unit, float distanceToTower, float distance, int directionX, int directionY)
{
    if(distance > 0)
    {
        unit->_xPos = unit->_xPos + (distance * (directionX - unit->_xPos))/ distanceToTower;
        unit->_yPos = unit->_yPos + (distance * (directionY - unit->_yPos))/ distanceToTower;
    }
}

/* Ataca */
int attackAttack(UNIT* unit, UNIT* target)
{
    int elapsedTime;

    elapsedTime = SDL_GetTicks() - unit->_lastAttackTime;

    if(unit->_meleeDamage > 0 && elapsedTime >= unit->_attackDelay){
        //Ataque a curta distância
        if(unit->_xPos >= target->_xPos && unit->_xPos <= target->_xPos + target->_width)
            if(unit->_yPos >= target->_yPos && unit->_yPos <= target->_yPos + target->_height)
            {
            //Unidade esta em posição
                takeDamage(target, unit->_meleeDamage);
                unit->_lastAttackTime = SDL_GetTicks();
                return unit->_meleeDamage;
            }
    }
    else if(unit->_rangedDamage > 0 && elapsedTime >= unit->_attackDelay){
        //Ataque a longa distância
        unit->_lastAttackTime = SDL_GetTicks();
        return unit->_rangedDamage;
    }

    return 0;
}

/* Atualiza o comportamento da unidade */
int attackUpdate(UNIT* unit, UNIT* target)
{
    int elapsedTime;
    float distanceToMove, distanceToTower;
    int defenceTowerX, defenceTowerY;
    int rangedAttackDamage = 0;

    defenceTowerY = target->_yPos + target->_height/2;
    defenceTowerX = target->_xPos + target->_width/2;

    //Calcula a distância entre a unidade e a torre
    distanceToTower = sqrt(pow((unit->_xPos - defenceTowerX), 2) + pow((unit->_yPos - defenceTowerY), 2));

    //Calcula a distância que a unidade deve percorrer
    elapsedTime = SDL_GetTicks() - unit->_lastIterationTime;
    distanceToMove = (float)(elapsedTime*unit->_speed)/1000;

    if(distanceToMove >= distanceToTower){
        //Caso a distância passe da torre
        distanceToMove = distanceToTower;
    }
    //Define a ação da unidade
    if((int)distanceToTower <= unit->_attackRange){
        //Para de andar e ataca a torre
        rangedAttackDamage = attackAttack(unit, target);
    }
    else if(distanceToMove >= 1.4){
        //Distancia percorrida movendo-se em uma unidade nos eixos X e Y
        attackMove(unit, distanceToTower, distanceToMove, defenceTowerX, defenceTowerY);
        unit->_lastIterationTime = SDL_GetTicks();
    }

    if(unit->_currentHealth == 0){
        return -1; // Devemos eliminar a unidade pois está morta
    }

    return rangedAttackDamage;
}

/* Cria um arqueiro */
UNIT createArcher()
{
    UNIT archer;

    archer = createUnit();
    //Determina os valores base de atributos
    archer._meleeDamage = 0;
    archer._baseHealth = 20;
    archer._baseArmour = 0;
    archer._baseRangedDamage = 10;
    archer._baseNumberOfTargets = 1;
    archer._baseAttackDelay = 500;
    archer._baseAttackRange = 300;
    //Determina os valores dos atributos
    archer._totalHealth = getAttributeValue(archer, HEALTH, archer._healthLevel);
    archer._armour = getAttributeValue(archer, ARMOUR, archer._healthLevel);
    archer._rangedDamage = getAttributeValue(archer, DAMAGE, archer._healthLevel);
    archer._numberOfTargets = getAttributeValue(archer, TARGETS, archer._healthLevel);
    archer._attackDelay = getAttributeValue(archer, DELAY, archer._healthLevel);
    archer._attackRange = getAttributeValue(archer, RANGE, archer._healthLevel);
    archer._currentHealth = archer._totalHealth;
    archer._reward = 15;
    archer._width = 10;
    archer._height = 10;
    archer._speed = 25;
    archer._unitType = ARCHER;
    //Atribui as funções
    archer.updateFunction = attackUpdate;
    archer.spawnFunction = attackSpawn;
    archer.renderFunction = render;
    archer.recoverHealthFunction = recoverHealth;

    return archer;
}

/* Cria um soldado */
UNIT createSoldier()
{
    UNIT soldier;

    soldier = createUnit();

    //Determina os valores base de atributos
    soldier._meleeDamage = 5;
    soldier._baseHealth = 30;
    soldier._baseArmour = 0;
    soldier._baseRangedDamage = 5;
    soldier._baseNumberOfTargets = 1;
    soldier._baseAttackDelay = 600;
    soldier._baseAttackRange = 20;
    //Determina os valores dos atributos
    soldier._totalHealth = getAttributeValue(soldier, HEALTH, soldier._healthLevel);
    soldier._armour = getAttributeValue(soldier, ARMOUR, soldier._healthLevel);
    soldier._rangedDamage = getAttributeValue(soldier, DAMAGE, soldier._healthLevel);
    soldier._numberOfTargets = getAttributeValue(soldier, TARGETS, soldier._healthLevel);
    soldier._attackDelay = getAttributeValue(soldier, DELAY, soldier._healthLevel);
    soldier._attackRange = getAttributeValue(soldier, RANGE, soldier._healthLevel);
    soldier._currentHealth = soldier._totalHealth;
    soldier._width = 10;
    soldier._height = 10;
    soldier._speed = 20;
    soldier._reward = 10;
    soldier._unitType = SOLDIER;
    //Atribui as funções
    soldier.updateFunction = attackUpdate;
    soldier.spawnFunction = attackSpawn;
    soldier.renderFunction = render;
    soldier.recoverHealthFunction = recoverHealth;


    return soldier;
}

/* Cria um cara com cavalo */
UNIT createHorseman()
{
    UNIT horseman;

    horseman = createUnit();

    //Determina os valores base de atributos
    horseman._meleeDamage = 10;
    horseman._baseHealth = 40;
    horseman._baseArmour = 0;
    horseman._baseRangedDamage = 0;
    horseman._baseNumberOfTargets = 1;
    horseman._baseAttackDelay = 500;
    horseman._baseAttackRange = 20;
    //Determina os valores dos atributos
    horseman._totalHealth = getAttributeValue(horseman, HEALTH, horseman._healthLevel);
    horseman._armour = getAttributeValue(horseman, ARMOUR, horseman._healthLevel);
    horseman._rangedDamage = getAttributeValue(horseman, DAMAGE, horseman._healthLevel);
    horseman._numberOfTargets = getAttributeValue(horseman, TARGETS, horseman._healthLevel);
    horseman._attackDelay = getAttributeValue(horseman, DELAY, horseman._healthLevel);
    horseman._attackRange = getAttributeValue(horseman, RANGE, horseman._healthLevel);
    horseman._currentHealth = horseman._totalHealth;
    horseman._reward = 30;
    horseman._width = 10;
    horseman._height = 10;
    horseman._speed = 35;
    horseman._unitType = HORSEMAN;
    //Atribui as funções
    horseman.updateFunction = attackUpdate;
    horseman.spawnFunction = attackSpawn;
    horseman.renderFunction = render;
    horseman.recoverHealthFunction = recoverHealth;

    return horseman;
}
