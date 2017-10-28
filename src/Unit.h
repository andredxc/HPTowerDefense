#include <stdlib.h>

class Unit{

    unsigned int _health, _armour, _dps;
    unsigned int _xPos, _yPos, _speed;
    bool _rangedAttack, _meleeAttack;

    virtual void spawn() = 0;
    virtual void move() = 0;
    virtual void attack() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    void takeDamage(uint damage);

    void setHealth(uint value);
    void setArmour(uint value);
    void setDps(uint value);
    void setRangedAttack(bool value);
    void setMeleeAttack(bool value);
    uint getHealth();
    uint getArmour();
    uint getDps();
    bool getRangedAttack();
    bool getMeleeAttack();

};
