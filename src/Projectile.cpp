#include "Projectile.h"

#include <SDL2/SDL_image.h>

Projectile::Projectile()
{
    _speed = -1;
    _damage = -1;
    _xPos = -1;
    _yPos = -1;
    _destXPos = -1;
    _destYPos = -1;
    _width = -1;
    _height = -1;
    _target = NULL;
    _visualTex = NULL;
}

Projectile::Projectile(int speed, int damage, int width, int height, int xPos, int yPos, Unit* target)
{
    _speed = speed;
    _damage = damage;
    _xPos = xPos;
    _yPos = yPos;
    _width = width;
    _height = height;
    _target = target;
    _visualTex = NULL;
}

Projectile::~Projectile()
{
    SDL_DestroyTexture(_visualTex);
}

void Projectile::update()
{
    
}

void Projectile::move(int distanceToTarget, int distance, int directionX, int directionY)
{
    if(distance > 0)
    {
        _xPos = _xPos + (distance * (directionX - _xPos))/ distanceToTarget;
        _yPos = _yPos + (distance * (directionY - _yPos))/ distanceToTarget;
    }
}

void Projectile::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;

    if(_xPos == -1 || _yPos == -1){
        fprintf(stderr, "Error, projectile has X or Y set to -1\n");
        return;
    }

    destRect.w = _width;
    destRect.h = _height;
    destRect.x = _xPos;
    destRect.y = _yPos;

    if(!renderer){
        fprintf(stderr, "Error rendering unit, renderer is NULL\n");
        return;
    }
    if(!_visualTex){
        //Define a texture da unidade
        tempSurface = IMG_Load("../img/projectile.bmp");
        if(tempSurface){
            _visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        }
        else{
            fprintf(stderr, "Error loading file for projectile\n");
        }
        SDL_FreeSurface(tempSurface);
    }
    // printf("(%p)Rendering projectile to X %d, Y: %d, width: %d, height: %d\n", _visualTex, destRect.x, destRect.y, destRect.w, destRect.h);
    SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
}

Unit* Projectile::getTarget(){ return _target; }
