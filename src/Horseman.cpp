#include "Horseman.h"

Horseman::Horseman()
{
}

Horseman::~Horseman()
{
    SDL_DestroyTexture(_visualTex);
}

void Horseman::print()
{
    printf("Archer at (%d,%d)\n", _xPos, _yPos);
}
