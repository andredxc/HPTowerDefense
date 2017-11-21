#include "Soldier.h"

Soldier::Soldier()
{
    _rangedAttack = 0;
}

Soldier::~Soldier()
{
    SDL_DestroyTexture(_visualTex);
}

void Soldier::print()
{
    printf("Archer at (%d,%d)\n", _xPos, _yPos);
}
