#ifndef X_Unit_h
#define X_Unit_h
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH      100000
#define GAME_HEIGHT     100000

enum UNIT_TYPE{TOWER, ARCHER, HORSEMAN, SOLDIER};

class Unit{

protected:
    int _health, _armour, _dps, _xPos, _yPos, _width, _height;
    int _rangedAttack, _meleeAttack, _attackRange;
    UNIT_TYPE _unitType;
    SDL_Texture *_visualTex;
    //Falta algum tipo de representação, SDL_Texture provavelmente

public:
    virtual void spawn(int screenWidth, int screenHeight) = 0;
    //virtual void update() = 0;

    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void takeDamage(int attackDamage);
    void setSize(int width, int height);
    void setHealth(int value);
    void setArmour(int value);
    void setDps(int value);
    void setRangedAttack(int value);
    void setMeleeAttack(int value);
    void setPosition(int x, int y);
    void setAttackRange(int value);
    int getHealth();
    int getArmour();
    int getDps();
    int getRangedAttack();
    int getMeleeAttack();
    int getXPos();
    int getYPos();
    int getAttackRange();
    UNIT_TYPE getUnitType();
    SDL_Texture* getTexture();
};
#endif
