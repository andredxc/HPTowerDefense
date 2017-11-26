#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "Unit.h"

Unit::Unit()
{
    _xPos = -1;
    _yPos = -1;
    _visualTex = NULL;
}

void Unit::takeDamage(int damage)
{
    _health = (damage - _armour) < 0 ? (_health) : _health - (damage - _armour);
}

void Unit::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;

    if(_xPos == -1 || _yPos == -1){
        spawn(screenWidth, screenHeight);
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
        fprintf(stderr, "Error rendering unit, visual texture is NULL\n");
        //Define a texture da unidade
        switch(_unitType){
            case SOLDIER: tempSurface = IMG_Load("../img/soldier.bmp"); break;
            case HORSEMAN: tempSurface = IMG_Load("../img/horseman.bmp"); break;
            case ARCHER: tempSurface = IMG_Load("../img/archer.bmp"); break;
            case DEFENCE: tempSurface = IMG_Load("../img/defence.bmp"); break;
            default: printf("Fatal internal error on render()\n");
        }
        if(tempSurface){
            _visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        }
        else{
            fprintf(stderr, "Error loading file for unitType = %d\n", _unitType);
        }
        SDL_FreeSurface(tempSurface);
    }
    printf("(%p)Rendering unit to X: %d, Y: %d, width: %d, height: %d\n", _visualTex, destRect.x, destRect.y, destRect.w, destRect.h);
    SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
}


void Unit::setSize(int width, int height){ _width = width; _height = height; }
void Unit::setHealth(int value){ _health = value; }
void Unit::setArmour(int value){ _armour = value; }
void Unit::setPosition(int x, int y){ _xPos = x; _yPos = y; }
int Unit::getHealth(){ return _health; }
int Unit::getArmour(){ return _health; }
int Unit::getXPos(){ return _xPos; }
int Unit::getYPos(){ return _yPos; }
UNIT_TYPE Unit::getUnitType(){ return _unitType; }
SDL_Texture* Unit::getTexture(){ return _visualTex; }
