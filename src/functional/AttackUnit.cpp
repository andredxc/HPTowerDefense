#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "AttackUnit.h"

AttackUnit::~AttackUnit()
{
    SDL_DestroyTexture(_visualTex);
}

int AttackUnit::update(Unit* target)
{
    int elapsedTime;
    float distanceToMove, distanceToTower;
    int defenceTowerX, defenceTowerY;
    int rangedAttackDamage = 0;

    //Calculo da posição da torre deve levar em consideração o tamanho
    // //Para que a unidade não fique em cima ou embaixo dela
    // if(_quadrant < 0 || _quadrant > 3){
    //     //Define o quadrante em que se encontra a unidade
    //     setQuadrant(target->getXPos(), target->getYPos());
    // }

    // switch(_quadrant){
    //     case 0:
    //         defenceTowerX = target->getXPos() + target->getWidth()/2;
    //         defenceTowerY = target->getYPos() - target->getHeight()/2;
    //         break;
    //     case 1:
    //         defenceTowerX = target->getXPos() + target->getWidth()/2;
    //         defenceTowerY = target->getYPos() + target->getHeight()/2;
    //         break;
    //     case 2:
    //         defenceTowerX = target->getXPos() - target->getWidth()/2;
    //         defenceTowerY = target->getYPos() - target->getHeight()/2;
    //         break;
    //     case 3:
    //         defenceTowerX = target->getXPos() - target->getWidth()/2;
    //         defenceTowerY = target->getYPos() + target->getHeight()/2;
    //         break;
    // }


    // if(_xPos > target->getXPos())
    // {
    //     defenceTowerX = target->getXPos() + target->getWidth()/2;
    // }
    // else
    // {
    //     defenceTowerX = target->getXPos() - target->getWidth()/2;
    // }

    // if(_yPos > target->getYPos())
    // {
    //     defenceTowerY = target->getYPos() + target->getHeight()/2;
    // }
    // else
    // {
    //     defenceTowerY = target->getYPos() - target->getHeight()/2;
    // }

    defenceTowerY = target->getYPos() + target->getHeight()/2;
    defenceTowerX = target->getXPos() + target->getWidth()/2;

    //Calcula a distância entre a unidade e a torre
    distanceToTower = sqrt(pow((_xPos - defenceTowerX), 2) + pow((_yPos - defenceTowerY), 2));

    //Calcula a distância que a unidade deve percorrer
    elapsedTime = SDL_GetTicks() - _lastIterationTime;
    distanceToMove = (float)(elapsedTime*_speed)/1000;

    if(distanceToMove >= distanceToTower){
        //Caso a distância passe da torre
        distanceToMove = distanceToTower;
    }
    //Define a ação da unidade
    if((int)distanceToTower <= _attackRange){
        //Para de andar e ataca a torre
        rangedAttackDamage = attack(target);
    }
    else if(distanceToMove >= 1.4){
        //Distancia percorrida movendo-se em uma unidade no eixo X e Y
        move(distanceToTower, distanceToMove, defenceTowerX, defenceTowerY);
        _lastIterationTime = SDL_GetTicks();
    }

    if(_currentHealth == 0){
        return -1; // Devemos eliminar a unidade pois está morta
    }

    return rangedAttackDamage;
}

void AttackUnit::spawn(int screenWidth, int screenHeight)
{
    int wall;

    //Define a parede da tela
    wall = rand() % 4;
    if(wall == 0 || wall == 1){
        //Paredes verticais
        _yPos = rand() % (screenHeight+1);
        //Define x de acordo com a parede da esquerda(wall==0) ou da direita(wall==1)
        _xPos = (wall == 0) ? 0 : screenWidth - _width; //Subtrai _width pois o desenho começa pela esquerda do objeto
        //printf("0 1 X: %d Y: %d\n",_xPos,_yPos);
    }
    else if(wall == 2 || wall == 3){
        //Paredes horizontais
        _xPos = rand() % (screenWidth+1);
        //Define y de acordo com a parede de baixo(wall==2) ou a de cima(wall==3)
        _yPos = (wall == 2) ? 0 : screenHeight - _height;
        //printf(" 2 3 X: %d Y: %d\n",_xPos,_yPos);

    }
    else{
        printf("Erro fatal - %s\n", __FUNCTION__);
    }
}

void AttackUnit::move(float distanceToTower, float distance, int directionX, int directionY)
{
    if(distance > 0)
    {
        _xPos = _xPos + (distance * (directionX - _xPos))/ distanceToTower;
        _yPos = _yPos + (distance * (directionY - _yPos))/ distanceToTower;
    }
}

int AttackUnit::attack(Unit* target)
{
    int elapsedTime;


    elapsedTime = SDL_GetTicks() - _lastAttackTime;
    // fprintf(stderr, "Elapsed time since last attack: %d\n", elapsedTime);

    if(_meleeDamage > 0 && elapsedTime >= _attackDelay){
        //Ataque a curta distância
        if(_xPos >= target->getXPos() && _xPos <= target->getXPos() + target->getWidth())
            if(_yPos >= target->getYPos() && _yPos <= target->getYPos() + target->getHeight())
        {
            //Unidade esta em posição
            target->takeDamage(_meleeDamage);
            _lastAttackTime = SDL_GetTicks();
            return _meleeDamage;
        }
    }
    else if(_rangedDamage > 0 && elapsedTime >= _attackDelay){
        //Ataque a longa distância
        _lastAttackTime = SDL_GetTicks();
        return _rangedDamage;
    }

    return 0;
}

int AttackUnit::getReward(){ return _reward; }
