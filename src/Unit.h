#ifndef UNIT_H
#define UNIT_H
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH      100000
#define GAME_HEIGHT     100000

enum UNIT_TYPE{DEFENCE, ARCHER, HORSEMAN, SOLDIER};

class Unit{

protected:
    int _health, _currentHealth, _armour;
    int _xPos, _yPos, _width, _height, _quadrant;
    int _rangedDamage, _meleeDamage, _attackRange, _attackDelay;    //_attackDelay em ms
    int _healthBarX, _healthBarY, _healthBarWidth, _healthBarHeight;
    Uint32 _lastIterationTime, _lastAttackTime;
    SDL_Texture *_visualTex;
    UNIT_TYPE _unitType;

public:
    virtual void spawn(int screenWidth, int screenHeight) = 0;
    virtual int update(Unit* target) = 0;
    //virtual void update() = 0;

    Unit();
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void renderHealthBar(SDL_Renderer* renderer);
    void takeDamage(int attackDamage);
    void setHealthBar(int xPos, int yPos, int width, int height);

    void setSize(int width, int height);
    void setHealth(int value);
    void setArmour(int value);
    void setPosition(int x, int y);
    int getHealth();
    int getArmour();
    int getXPos();
    int getYPos();
    int getWidth();
    int getHeight();
    UNIT_TYPE getUnitType();
    SDL_Texture* getTexture();

protected:
    void setQuadrant(int destX, int destY);
};
#endif
