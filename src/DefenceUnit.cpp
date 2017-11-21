#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

DefenceUnit::DefenceUnit()
{
}

void DefenceUnit::spawn(int screenWidth, int screenHeight)
{
	_xPos = screenWidth/2;
	_yPos = screenHeight/2;
}
void DefenceUnit::move()
{

}
