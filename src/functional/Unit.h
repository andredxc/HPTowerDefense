#ifndef UNIT_H
#define UNIT_H
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH          100000
#define GAME_HEIGHT         100000
#define ARCHER_BMP_FILE             "../../img/archer.bmp"
#define HORSEMAN_BMP_FILE           "../../img/horseman.bmp"
#define SOLDIER_BMP_FILE 	  	    "../../img/soldier.bmp"
#define DEFENCE_BMP_FILE 		    "../../img/defence.bmp"
#define HEALTHBAR_GREEN_BMP_FILE    "../../img/healthBarGreen.bmp"
#define HEALTHBAR_RED_BMP_FILE 		"../../img/healthBarRed.bmp"

enum UNIT_TYPE{DEFENCE, ARCHER, HORSEMAN, SOLDIER,PROJECTILE};
enum ATTRIBUTE{HEALTH, ARMOUR, DAMAGE, TARGETS, DELAY, RANGE};

typedef struct Unit{

    int _currentHealth;
    int _xPos, _yPos, _width, _height;
    int _meleeDamage;
    int _healthBarX, _healthBarY, _healthBarWidth, _healthBarHeight;
    int _healthLevel, _armourLevel, _damageLevel, _targetsLevel, _delayLevel, _rangeLevel;
    int _totalHealth, _armour, _rangedDamage, _numberOfTargets, _attackDelay, _attackRange;
    int _baseHealth, _baseArmour, _baseRangedDamage, _baseNumberOfTargets, _baseAttackDelay, _baseAttackRange;
    uint _speed, _directionX, _directionY;
    int _reward;
    Uint32 _lastIterationTime, _lastAttackTime;
    SDL_Texture *_visualTex;
    UNIT_TYPE _unitType;
    // Ponteiros para funções
    int (*attackFunction)(struct Unit* unit, struct Unit* target);
    void (*moveFunction)(struct Unit* unit, float distanceToTower, float distance, int directionX, int directionY);
    int (*updateFunction)(struct Unit* unit, int screenWidth, int screenHeight);
    void (*spawnFunction)(struct Unit* unit, int screenWidth, int screenHeight);

} UNIT;

UNIT createUnit();
bool render(UNIT* unit, SDL_Renderer* renderer, int screenWidth, int screenHeight);
void renderHealthBar(UNIT unit, SDL_Renderer* renderer);
void takeDamage(UNIT* unit, int attackDamage);
void setHealthBar(UNIT unit, int xPos, int yPos, int width, int height);

int getAttributeLevel(UNIT unit, ATTRIBUTE attr);
int getAttributeValue(UNIT unit, ATTRIBUTE attr, int level);
int getAttributeUpgradeCost(UNIT unit, ATTRIBUTE attr);
void incAttributeLevel(UNIT* unit, ATTRIBUTE attr);


#endif
