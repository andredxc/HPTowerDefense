#include <stdlib.h>

class Unit{

protected:
    unsigned int _health, _armour, _dps, _xPos, _yPos;
    unsigned int _rangedAttack, _meleeAttack, _attackRange;
    //Falta algum tipo de representação, SDL_Texture provavelmente

public:
    virtual void spawn() = 0;
    virtual void update() = 0;

    void render();
    void takeDamage(uint attackDamage);

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
