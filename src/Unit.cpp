#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "Unit.h"

Unit::Unit()
{
    _xPos = -1;
    _yPos = -1;
    _visualTex = NULL;
    _lastIterationTime = SDL_GetTicks();
    _lastAttackTime = _lastIterationTime;
    _healthBarWidth = -1;
    _healthBarHeight = -1;
    //Inicializa o nível dos atributos
    _healthLevel = 1;
    _armourLevel = 1;
    _damageLevel = 1;
    _targetsLevel = 1;
    _delayLevel = 1;
    _rangeLevel = 1;
}

void Unit::takeDamage(int damage)
{
    int damageBlock;

    damageBlock = (float)damage/100 * _armour;
    _currentHealth -= (damage - damageBlock);
    if(_currentHealth < 0){
        _currentHealth = 0;
    }
}

void Unit::setHealthBar(int xPos, int yPos, int width, int height)
{
    _healthBarX = xPos;
    _healthBarY = yPos;
    _healthBarWidth = width;
    _healthBarHeight = height;
}

bool Unit::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;
    int returnValue;

    if(_xPos == -1 || _yPos == -1){
        spawn(screenWidth, screenHeight);
    }

    destRect.w = _width;
    destRect.h = _height;
    destRect.x = _xPos;
    destRect.y = _yPos;

    if(!renderer){
        fprintf(stderr, "Error rendering unit, renderer is NULL\n");
        return false;
    }
    if(!_visualTex){
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
    returnValue = SDL_RenderCopy(renderer, _visualTex, NULL, &destRect);
    renderHealthBar(renderer);

    if(returnValue < 0){
        // Caso de erro, pode ser culpa da textura desalocada
        SDL_DestroyTexture(_visualTex);
        _visualTex = NULL;
        return false;
    }

    return true;
}

void Unit::renderHealthBar(SDL_Renderer* renderer)
{
    int currentHealthWidth = 0, healthLostWidth = 0;
    SDL_Rect destRect;
    SDL_Surface* tempSurface;
    SDL_Texture* tempTexture;

    if(_healthBarX < 0 || _healthBarY < 0 || _healthBarWidth < 0 || _healthBarHeight < 0)
    {
        //Barra de vida não foi definida
        return;
    }

    //Desenha a vida atual
    currentHealthWidth = ((float)_healthBarWidth/(float)_totalHealth) * _currentHealth;
    tempSurface = IMG_Load("../img/healthBarGreen.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(!tempTexture){
        printf("Error loading healthBarGreen\n");
        return;
    }
    destRect.x = _healthBarX;
    destRect.y = _healthBarY;
    destRect.w = currentHealthWidth;
    destRect.h = _healthBarHeight;
    SDL_RenderCopy(renderer, tempTexture, NULL, &destRect);
    //Desenha a vida perdida, se for maior que 0
    healthLostWidth = _healthBarWidth - currentHealthWidth;
    if(healthLostWidth == 0)
    {
        //Vida está cheia
        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(tempTexture);
        return;
    }
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
    tempSurface = IMG_Load("../img/healthBarRed.bmp");
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(!tempTexture){
        printf("Error loading healthBarRed\n");
        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(tempTexture);
        return;
    }
    destRect.x = _healthBarX + currentHealthWidth;
    destRect.y = _healthBarY;
    destRect.w = healthLostWidth;
    destRect.h = _healthBarHeight;
    SDL_RenderCopy(renderer, tempTexture, NULL, &destRect);
}

int Unit::getHealth(){ return _currentHealth; }
int Unit::getTotalHealth(){ return _totalHealth; }
int Unit::getArmour(){ return _armour; }
int Unit::getXPos(){ return _xPos; }
int Unit::getYPos(){ return _yPos; }
int Unit::getWidth(){ return _width; }
int Unit::getHeight(){ return _height; }
int Unit::getAttackRange(){ return _attackRange; }
int Unit::getRangedDamage(){ return _rangedDamage; }
int Unit::getAttackDelay(){ return _attackDelay; }
int Unit::getNumberOfTargets(){ return _numberOfTargets; }
UNIT_TYPE Unit::getUnitType(){ return _unitType; }
SDL_Texture* Unit::getTexture(){ return _visualTex; }

int Unit::getAttributeLevel(ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: return _healthLevel;
        case ARMOUR: return _armourLevel;
        case DAMAGE: return _damageLevel;
        case TARGETS: return _targetsLevel;
        case DELAY: return _delayLevel;
        case RANGE: return _rangeLevel;
        default: return -1;
    }
}

int Unit::getAttributeValue(ATTRIBUTE attr, int level)
{
    switch(attr){
        case HEALTH: return _baseHealth + (level-1)*20;
        case ARMOUR: return _baseArmour + (level-1)*3;
        case DAMAGE: return _baseRangedDamage + (level-1)*5;
        case TARGETS: return _baseNumberOfTargets + (level-1)*1;
        case DELAY: return _baseAttackDelay - (level-1)*30;
        case RANGE: return _baseAttackRange + (level-1)*10;
        default: return -1;
    }
}

int Unit::getAttributeUpgradeCost(ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: return _healthLevel*20;
        case ARMOUR: return _armourLevel*10;
        case DAMAGE: return _damageLevel*20;
        case TARGETS: return _targetsLevel*60;
        case DELAY: return _delayLevel*10;
        case RANGE: return _rangeLevel*15;
        default: return -1;
    }
}

void Unit::incAttributeLevel(ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: _healthLevel++; _totalHealth = getAttributeValue(HEALTH, _healthLevel); break;
        case ARMOUR: _armourLevel++; _armour = getAttributeValue(ARMOUR, _armourLevel); break;
        case DAMAGE: _damageLevel++; _rangedDamage = getAttributeValue(DAMAGE, _damageLevel); break;
        case TARGETS: _targetsLevel++; _numberOfTargets = getAttributeValue(TARGETS, _targetsLevel); break;
        case DELAY: _delayLevel++; _attackDelay = getAttributeValue(DELAY, _delayLevel); break;
        case RANGE: _rangeLevel++; _attackRange = getAttributeValue(RANGE, _rangeLevel); break;
    }
}
