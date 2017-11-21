#include <stdio.h>
#include "Unit.h"

void Unit::takeDamage(uint damage){

    _health = (damage - _armour) < 0 ? (_health) : _health - (damage - _armour);
}

void Unit::render(SDL_Renderer* renderer, int screenWidth, int screenHeight){

    SDL_Rect destRect;

    destRect.w = _width;
    destRect.h = _height;
    destRect.x = _xPos;
    destRect.y = _yPos;

    if(!renderer){
        printf("Error rendering unit, renderer is NULL\n");
    }
    if(!_visualTex){
        printf("Error rendering unit, visual texture is NULL\n");
    }
    else{
        printf("Rendering archer to X: %d, Y: %d, width: %d, height: %d\n", destRect.x, destRect.y, destRect.w, destRect.h);
        SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
    }
}


void Unit::setSize(uint width, uint height){ _width = width; _height = height; }
void Unit::setHealth(uint value){ _health = value; }
void Unit::setArmour(uint value){ _armour = value; }
void Unit::setDps(uint value){ _dps = value; }
void Unit::setRangedAttack(uint value){ _rangedAttack = value; }
void Unit::setMeleeAttack(uint value){ _meleeAttack = value; }
void Unit::setPosition(uint x, uint y){ _xPos = x; _yPos = y; }
void Unit::setAttackRange(uint value){ _attackRange = value; }
uint Unit::getHealth(){ return _health; }
uint Unit::getArmour(){ return _health; }
uint Unit::getDps(){ return _dps; }
uint Unit::getRangedAttack(){ return _rangedAttack; }
uint Unit::getMeleeAttack(){ return _meleeAttack; }
uint Unit::getXPos(){ return _xPos; }
uint Unit::getYPos(){ return _yPos; }
uint Unit::getAttackRange(){ return _attackRange; }
