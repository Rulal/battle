#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include "signaltype.h"
#include "structures.h"
#include "buff.h"

#include <list>

class Unit;
class Effect;

class BattleController
{
public:
    BattleController(uint8 teamCount, uint8 sizeTeam);
    ~BattleController();

    void gameTick();
    void trySpellCast();
    void signalActive(const Signal signalType, SignalStruct& signalStruct = invalidSignalStruct);
    Unit& getUnit(uint8 idUnit);
    void addUserAction(UserAction action);
    void removeUserAction(UserAction action);

private:
    void sortSpeedList();
    void actionBuff(const Signal signalType, SignalStruct& signalStruct);
    void removeInActiveBuff();

//    callback loadStats;
//    callback loadSpell;

    const uint8 _teamsCount;
    const uint8 _sizeTeam;

    std::list<Buff> _activeEffects;

//    Unit** _teams;
//    uint8** _placement;
    stat* _speedList;
    Unit* _units;

    std::list<UserAction>* _userActions;

    uint8 signalsCyclesCount = 0;
};
#endif // BATTLECONTROLLER_H
