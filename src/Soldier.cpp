#include "Soldier.h"

Soldier::Soldier()
{
    _rangedAttack = 0;
    setColor(0, 0, 255);
}

Soldier::~Soldier()
{
    SDL_DestroyTexture(_visualTex);
}
