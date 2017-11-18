#include <stdio.h>
#include <stdlib.h>
#include "AttackUnit.h"

void AttackUnit::spawn(uint maxX, uint maxY){

    int wall;

    //Define a parede da tela
    wall = rand() % 4;
    if(wall == 0 || wall == 1){
        //Paredes verticais
        _yPos = rand() % (maxY+1);
        //Define x de acordo com a parede da esquerda(wall==0) ou da direita(wall==1)
        _xPos = (wall == 0) ? 0 : maxX;
        printf("0 1 X: %d Y: %d\n",_xPos,_yPos);
    }
    else if(wall == 2 || wall == 3){
        //Paredes horizontais
        _xPos = rand() % (maxX+1);
        //Define y de acordo com a parede de baixo(wall==2) ou a de cima(wall==3)
        _yPos = (wall == 2) ? 0 : maxY;
        printf(" 2 3 X: %d Y: %d\n",_xPos,_yPos);
        _yPos = 0;

    }
    else{
        printf("Erro fatal - %s\n", __FUNCTION__);
    }
}

void AttackUnit::move(){

}
