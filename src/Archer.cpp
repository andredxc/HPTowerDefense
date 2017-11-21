#include "Archer.h"
#include <SDL2/SDL_image.h>

Archer::Archer()
{
}

Archer::Archer(SDL_Renderer* renderer)
{
    SDL_Surface *tempSurface;

    //Inicializa atributos
    _width = 10;
    _height = 10;
    //Inicializa texture do boneco
    tempSurface = IMG_Load("../img/archer.bmp");
    _visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Archer::~Archer()
{
	SDL_DestroyTexture(_visualTex);
}

void Archer::print()
{
    printf("Archer at (%d,%d) with size %dx%d\n", _xPos, _yPos, _width, _height);
}

/*
void Archer::update(){


}
*/
