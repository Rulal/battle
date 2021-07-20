#ifndef UNIT_H
#define UNIT_H

#include "defines.h"
#include "structures.h"
#include "buff.h"


class BattleController;

class Unit
{
public:
    static bool isFaster(const Unit& left, const Unit& right);

    Unit();
    ~Unit();
    void init(uint8 id, uint8 team, uint8 place, BattleController* battleController);

//    void setBattleController(BattleController* battleController);
    void gameTick();
    bool isDead() const;
    bool activateSpell(uint8 spellId, uint8 target);


    void gettingSP(stat sp, uint8 idOwner);
//    void spendSP(stat sp, uint8 idOwner);
    void gettingDMG(stat dmg, uint8 idOwner);
    void gettingHeal(stat heal, uint8 idOwner);
    void gettingHP(stat hp, uint8 idOwner);

private:
    uint8 _id = INVALID_ID_8;
    uint8 _team;
    uint8 _place;

    stat _maxHP;
    int _curHP;          //TO DO: remove int

    stat _maxSP;
    stat _thresholdSP;
    stat _curSP;

    stat _damage;
    stat _defense;
    stat _speed;

    Buff spells[MAX_COUNT_SPELLS];

    BattleController* _battleController;
};

#endif // UNIT_H
