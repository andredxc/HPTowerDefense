#ifndef X_Unit_h
#define X_Unit_h
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH      100000
#define GAME_HEIGHT     100000

class Unit{

protected:
    unsigned int _health, _armour, _dps, _xPos, _yPos, _width, _height;
    unsigned int _rangedAttack, _meleeAttack, _attackRange;
    SDL_Texture *_visualTex;
    //Falta algum tipo de representação, SDL_Texture provavelmente

public:
    virtual void spawn() = 0;
    //virtual void update() = 0;

    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void takeDamage(uint attackDamage);
    void setSize(uint width, uint height);
    void setColor(uint r, uint g, uint b);
    void setHealth(uint value);
    void setArmour(uint value);
    void setDps(uint value);
    void setRangedAttack(uint value);
    void setMeleeAttack(uint value);
    void setPosition(uint x, uint y);
    void setAttackRange(uint value);
    uint getHealth();
    uint getArmour();
    uint getDps();
    uint getRangedAttack();
    uint getMeleeAttack();
    uint getXPos();
    uint getYPos();
    uint getAttackRange();
};
#endif
