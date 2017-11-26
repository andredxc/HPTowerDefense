#include <stdio.h>
#include <stdlib.h>
#include "AttackUnit.h"

AttackUnit::~AttackUnit()
{
    SDL_DestroyTexture(_visualTex);
}

void AttackUnit::update(Unit* target)
{
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
        _yPos = 0;

    }
    else{
        printf("Erro fatal - %s\n", __FUNCTION__);
    }
}

void AttackUnit::move(int distance, int directionX, int directionY)
{
    printf("Oi\n");
}

void AttackUnit::attack(Unit* target)
{
    printf("Oi\n");
}
