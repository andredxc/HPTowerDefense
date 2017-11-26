#include "Soldier.h"

Soldier::Soldier()
{
    _rangedDps = 0;
}

Soldier::~Soldier()
{
    SDL_DestroyTexture(_visualTex);
}
