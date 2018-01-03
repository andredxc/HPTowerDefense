#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "Unit.h"

/* Inicializa uma unidade */
UNIT createUnit()
{
    UNIT newUnit;

    newUnit._xPos = -1;
    newUnit._yPos = -1;
    newUnit._visualTex = NULL;
    newUnit._lastIterationTime = SDL_GetTicks();
    newUnit._lastAttackTime = newUnit._lastIterationTime;
    newUnit._healthBarWidth = -1;
    newUnit._healthBarHeight = -1;
    //Inicializa o nível dos atributos
    newUnit._healthLevel = 1;
    newUnit._armourLevel = 1;
    newUnit._damageLevel = 1;
    newUnit._targetsLevel = 1;
    newUnit._delayLevel = 1;
    newUnit._rangeLevel = 1;

    return newUnit;
}

/* Desaloca os dados referentes a uma unidade */
void deleteUnit(UNIT* unit)
{
    SDL_DestroyTexture(unit->_visualTex);
}

/* Recupera totalmente a vida de uma unidade */
void recoverHealth(UNIT* unit)
{
    unit->_currentHealth = unit->_totalHealth;
}

/* Tira vida da unidade de acordo com o dano de ataque */
void takeDamage(UNIT* unit, int damage)
{
    int damageBlock;

    damageBlock = (float)damage/100 * unit->_armour;
    unit->_currentHealth -= (damage - damageBlock);
    if(unit->_currentHealth < 0){
        unit->_currentHealth = 0;
    }
}

/* Renderiza uma unidade */
bool render(UNIT* unit, SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    SDL_Rect destRect;
    SDL_Surface* tempSurface;
    int returnValue;

    destRect.w = unit->_width;
    destRect.h = unit->_height;
    destRect.x = unit->_xPos;
    destRect.y = unit->_yPos;

    if(!renderer){
        fprintf(stderr, "Error rendering unit, renderer is NULL\n");
        return false;
    }
    if(!unit->_visualTex){
        //Define a texture da unidade
        switch(unit->_unitType){
            case SOLDIER: tempSurface = IMG_Load(SOLDIER_BMP_FILE); break;
            case HORSEMAN: tempSurface = IMG_Load(HORSEMAN_BMP_FILE); break;
            case ARCHER: tempSurface = IMG_Load(ARCHER_BMP_FILE); break;
            case DEFENCE: tempSurface = IMG_Load(DEFENCE_BMP_FILE); break;
            default: printf("Fatal internal error on render()\n");
        }
        if(tempSurface){
            unit->_visualTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
        }
        else{
            fprintf(stderr, "Error loading file for unitType = %d\n", unit->_unitType);
        }
        SDL_FreeSurface(tempSurface);
    }
    returnValue = SDL_RenderCopy(renderer, unit->_visualTex, NULL, &destRect);
    unitRenderHealthBar(*unit, renderer);

    if(returnValue < 0){
        // Caso de erro, pode ser culpa da textura desalocada
        SDL_DestroyTexture(unit->_visualTex);
        unit->_visualTex = NULL;
        return false;
    }

    return true;
}

/* Define uma barra que mostra a vida de uma unidade */
void unitSetHealthBar(UNIT* unit, int xPos, int yPos, int width, int height)
{
    unit->_healthBarX = xPos;
    unit->_healthBarY = yPos;
    unit->_healthBarWidth = width;
    unit->_healthBarHeight = height;
}

/* Desenha a barra de vida */
void unitRenderHealthBar(UNIT unit, SDL_Renderer* renderer)
{
    int currentHealthWidth = 0, healthLostWidth = 0;
    SDL_Rect destRect;
    SDL_Surface* tempSurface;
    SDL_Texture* tempTexture;

    if(unit._healthBarX < 0 || unit._healthBarY < 0 || unit._healthBarWidth < 0 || unit._healthBarHeight < 0){
        //Barra de vida não foi definida
        return;
    }

    //Desenha a vida atual
    currentHealthWidth = ((float)unit._healthBarWidth/(float)unit._totalHealth) * unit._currentHealth;
    tempSurface = IMG_Load(HEALTHBAR_GREEN_BMP_FILE);
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(!tempTexture){
        printf("Error loading healthBarGreen\n");
        return;
    }
    destRect.x = unit._healthBarX;
    destRect.y = unit._healthBarY;
    destRect.w = currentHealthWidth;
    destRect.h = unit._healthBarHeight;
    SDL_RenderCopy(renderer, tempTexture, NULL, &destRect);
    //Desenha a vida perdida, se for maior que 0
    healthLostWidth = unit._healthBarWidth - currentHealthWidth;
    if(healthLostWidth == 0){
        //Vida está cheia
        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(tempTexture);
        return;
    }
    SDL_FreeSurface(tempSurface);
    SDL_DestroyTexture(tempTexture);
    tempSurface = IMG_Load(HEALTHBAR_RED_BMP_FILE);
    tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(!tempTexture){
        printf("Error loading healthBarRed\n");
        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(tempTexture);
        return;
    }
    destRect.x = unit._healthBarX + currentHealthWidth;
    destRect.y = unit._healthBarY;
    destRect.w = healthLostWidth;
    destRect.h = unit._healthBarHeight;
    SDL_RenderCopy(renderer, tempTexture, NULL, &destRect);
}

/* Retorna as moedas ganhas por matar a unidade */
int unitGetReward(UNIT* unit)
{
    if(unit->_reward == 0)
    {
        return 0;
    }
    int reward = unit->_reward;
    // Evita que a mesma recompensa seja dada mais de uma vez
    unit->_reward = 0;
    return reward;
}

/* Retorna o nível de um atributo */
int getAttributeLevel(UNIT unit, ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: return unit._healthLevel;
        case ARMOUR: return unit._armourLevel;
        case DAMAGE: return unit._damageLevel;
        case TARGETS: return unit._targetsLevel;
        case DELAY: return unit._delayLevel;
        case RANGE: return unit._rangeLevel;
        default: return -1;
    }
}

/* Retorna o valor de um atributo */
int getAttributeValue(UNIT unit, ATTRIBUTE attr, int level)
{
    switch(attr){
        case HEALTH: return unit._baseHealth + (level-1)*20;
        case ARMOUR: return unit._baseArmour + (level-1)*3;
        case DAMAGE: return unit._baseRangedDamage + (level-1)*5;
        case TARGETS: return unit._baseNumberOfTargets + (level-1)*1;
        case DELAY: return unit._baseAttackDelay - (level-1)*30;
        case RANGE: return unit._baseAttackRange + (level-1)*10;
        default: return -1;
    }
}

/* Retorna o custo para aumentar o nível de um atributo */
int getAttributeUpgradeCost(UNIT unit, ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: return unit._healthLevel*20;
        case ARMOUR: return unit._armourLevel*10;
        case DAMAGE: return unit._damageLevel*20;
        case TARGETS: return unit._targetsLevel*60;
        case DELAY: return unit._delayLevel*10;
        case RANGE: return unit._rangeLevel*15;
        default: return -1;
    }
}

/* Incrementa o nível de um atributo */
void incAttributeLevel(UNIT* unit, ATTRIBUTE attr)
{
    switch(attr){
        case HEALTH: unit->_healthLevel++; unit->_totalHealth = getAttributeValue(*unit, HEALTH, unit->_healthLevel); break;
        case ARMOUR: unit->_armourLevel++; unit->_armour = getAttributeValue(*unit, ARMOUR, unit->_armourLevel); break;
        case DAMAGE: unit->_damageLevel++; unit->_rangedDamage = getAttributeValue(*unit, DAMAGE, unit->_damageLevel); break;
        case TARGETS: unit->_targetsLevel++; unit->_numberOfTargets = getAttributeValue(*unit, TARGETS, unit->_targetsLevel); break;
        case DELAY: unit->_delayLevel++; unit->_attackDelay = getAttributeValue(*unit, DELAY, unit->_delayLevel); break;
        case RANGE: unit->_rangeLevel++; unit->_attackRange = getAttributeValue(*unit, RANGE, unit->_rangeLevel); break;
    }
}
