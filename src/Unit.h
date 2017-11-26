#ifndef UNIT_H
#define UNIT_H
#include <stdlib.h>
#include <SDL2/SDL.h>

#define GAME_WIDTH      100000
#define GAME_HEIGHT     100000

enum UNIT_TYPE{DEFENCE, ARCHER, HORSEMAN, SOLDIER};

class Unit{

protected:
    int _health, _armour, _dps, _xPos, _yPos, _width, _height;
    int _rangedDps, _meleeDps, _attackRange;
    UNIT_TYPE _unitType;
    SDL_Texture *_visualTex;
    //Falta algum tipo de representação, SDL_Texture provavelmente

public:
    virtual void spawn(int screenWidth, int screenHeight) = 0;
    virtual void update(Unit* target) = 0;
    //virtual void update() = 0;

    Unit();
    void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    void takeDamage(int attackDamage);
    
    void setSize(int width, int height);
    void setHealth(int value);
    void setArmour(int value);
    void setPosition(int x, int y);
    int getHealth();
    int getArmour();
    int getXPos();
    int getYPos();
    UNIT_TYPE getUnitType();
    SDL_Texture* getTexture();
};
#endif
