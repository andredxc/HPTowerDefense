#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

DefenceUnit::DefenceUnit()
{
    //Inicializa os atributos padrão da torre de defesa
    _health = 100;
    _armour = 5;
    _meleeDps = 0;
    _rangedDps = 5;
    _width = 40;
    _height = 40;
    _unitType = DEFENCE;
}

void DefenceUnit::spawn(int screenWidth, int screenHeight)
{
	_xPos = screenWidth/2 - _width/2;
	_yPos = screenHeight/2 - _height/2;
}
void DefenceUnit::move()
{

}
