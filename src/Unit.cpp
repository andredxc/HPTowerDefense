#include <stdio.h>
#include "Unit.h"

void Unit::takeDamage(uint damage){

    _health = (damage - _armour) < 0 ? (_health) : _health - (damage - _armour);
}

void Unit::render(SDL_Renderer* renderer, int screenWidth, int screenHeight){

    SDL_Rect destRect;
    int widthRatio, heightRatio;

    //Permite que a lógica do independa da resolução real da tela
    widthRatio = screenWidth/GAME_WIDTH;
    heightRatio = screenHeight/GAME_HEIGHT;

    destRect.w = _width*widthRatio;
    destRect.h = _height*heightRatio;
    destRect.x = _xPos*widthRatio;
    destRect.y = _yPos*widthRatio;

    if(!renderer || !_visualTex){
        fprintf(stderr, "Unit - Error rendering unit\n");
    }
    else{
        SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
    }
}

void Unit::setSize(uint width, uint height){ _width = width; _height = height; }
void Unit::setColor(uint r, uint g, uint b){ SDL_SetTextureColorMod(_visualTex, r, g, b); }
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
