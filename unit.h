#ifndef UNIT_H
#define UNIT_H

#include "defines.h"
#include "structures.h"

class BattleController;

class Unit
{
public:
    Unit();
    ~Unit();
    void init(uint8 id, uint8 team, uint8 place, BattleController* battleController);

//    void setBattleController(BattleController* battleController);
    void gameTick();
    bool isDead() const;

    static bool isFaster(const Unit& left, const Unit& right);

    void gettingSP(stat sp, uint8 idOwner);
    void gettingDMG(stat dmg, uint8 idOwner);
    void gettingHeal(stat heal, uint8 idOwner);
    void gettingHP(stat hp, uint8 idOwner);

private:
    uint8 _id = INVALID_ID;
    uint8 _team;
    uint8 _place;

    stat _maxHP;
    stat _curHP;

    stat _maxSP;
    stat _thresholdSP;
    stat _curSP;

    stat _damage;
    stat _defense;
    stat _speed;

    BattleController* _battleController;
};

#endif // UNIT_H
