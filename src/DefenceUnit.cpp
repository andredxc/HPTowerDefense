#include <stdio.h>
#include <stdlib.h>
#include "DefenceUnit.h"

DefenceUnit::DefenceUnit(){

    setColor(255, 255, 255);
}

void DefenceUnit::spawn(){

	_xPos = GAME_WIDTH/2;
	_yPos = GAME_HEIGHT/2;

}
void DefenceUnit::move(){

}
