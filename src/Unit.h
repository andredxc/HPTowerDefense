#ifndef UNIT_H
#define UNIT_H
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH      100000
#define GAME_HEIGHT     100000

enum UNIT_TYPE{DEFENCE, ARCHER, HORSEMAN, SOLDIER,PROJECTILE};
enum ATTRIBUTE{HEALTH, ARMOUR, DAMAGE, TARGETS, DELAY, RANGE};

class Unit{

protected:
    int _currentHealth;
    int _xPos, _yPos, _width, _height;
    int _meleeDamage;
    int _healthBarX, _healthBarY, _healthBarWidth, _healthBarHeight;
    int _healthLevel, _armourLevel, _damageLevel, _targetsLevel, _delayLevel, _rangeLevel;
    int _totalHealth, _armour, _rangedDamage, _numberOfTargets, _attackDelay, _attackRange;
    int _baseHealth, _baseArmour, _baseRangedDamage, _baseNumberOfTargets, _baseAttackDelay, _baseAttackRange;
    Uint32 _lastIterationTime, _lastAttackTime;
    SDL_Texture *_visualTex;
    UNIT_TYPE _unitType;


public:
    virtual void spawn(int screenWidth, int screenHeight) = 0;
    virtual int update(Unit* target) = 0;

    Unit();
    bool render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void renderHealthBar(SDL_Renderer* renderer);
    void takeDamage(int attackDamage);
    void setHealthBar(int xPos, int yPos, int width, int height);

    int getTotalHealth();
    int getHealth();
    int getArmour();
    int getXPos();
    int getYPos();
    int getWidth();
    int getHeight();
    int getAttackRange();
    int getRangedDamage();
    int getAttackDelay();
    int getNumberOfTargets();
    int getAttributeLevel(ATTRIBUTE attr);
    int getAttributeValue(ATTRIBUTE attr, int level);
    int getAttributeUpgradeCost(ATTRIBUTE attr);
    void incAttributeLevel(ATTRIBUTE attr);
    UNIT_TYPE getUnitType();
    SDL_Texture* getTexture();
};
#endif
