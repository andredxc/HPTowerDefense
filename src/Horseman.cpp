#include "Horseman.h"

Horseman::Horseman()
{
    setColor(0, 255, 0);
}

Horseman::~Horseman()
{
    SDL_DestroyTexture(_visualTex);
}
