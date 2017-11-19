#include <stdio.h>
#include <stdlib.h>
#include "AttackUnit.h"

void AttackUnit::spawn(){

    int wall;

    //Define a parede da tela
    wall = rand() % 4;
    if(wall == 0 || wall == 1){
        //Paredes verticais
        _yPos = rand() % (GAME_HEIGHT+1);
        //Define x de acordo com a parede da esquerda(wall==0) ou da direita(wall==1)
        _xPos = (wall == 0) ? 0 : GAME_WIDTH;
        printf("0 1 X: %d Y: %d\n",_xPos,_yPos);
    }
    else if(wall == 2 || wall == 3){
        //Paredes horizontais
        _xPos = rand() % (GAME_WIDTH+1);
        //Define y de acordo com a parede de baixo(wall==2) ou a de cima(wall==3)
        _yPos = (wall == 2) ? 0 : GAME_HEIGHT;
        printf(" 2 3 X: %d Y: %d\n",_xPos,_yPos);
        _yPos = 0;

    }
    else{
        printf("Erro fatal - %s\n", __FUNCTION__);
    }
}

void AttackUnit::move(){

}
