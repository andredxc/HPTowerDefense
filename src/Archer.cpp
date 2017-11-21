#include "Archer.h"

Archer::Archer()
{
	//printf("Construtor Archer\n");
    _meleeAttack = 0;
    setColor(255, 0, 0);
}

Archer::~Archer()
{
	SDL_DestroyTexture(_visualTex);
}

/*
void Archer::update(){


}
*/
