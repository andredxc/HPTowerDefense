#include "Archer.h"
#include <SDL2/SDL_image.h>

Archer::Archer()
{
    _width = 10;
    _height = 10;
    _xPos = -1;
    _yPos = -1;
    _unitType = ARCHER;
}

Archer::~Archer()
{
	//SDL_DestroyTexture(_visualTex);
}

void Archer::print()
{
    printf("Archer at (%d,%d) with size %dx%d\n", _xPos, _yPos, _width, _height);
}

/*
void Archer::update(){


}
*/
