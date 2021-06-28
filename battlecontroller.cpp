#include "battlecontroller.h"
#include "unit.h"

BattleController::BattleController(uint8 teamsCount, uint8 sizeTeam) :
    _teamsCount(teamsCount),
    _sizeTeam(sizeTeam)
{
    _units = new Unit[_teamsCount * _teamsCount];
    _speedList = new stat[_teamsCount * _teamsCount];

    for (uint8 i = 0; i < _teamsCount * _teamsCount; i++)
    {
        _units[i].setBattleController(this);
    }

//    _teams = new Unit*[_teamsCount];
//    _placement = new uint8*[_teamsCount];
//    for (uint8 i = 0; i < _teamsCount; ++i)
//    {
//        _teams[i] = new Unit[_teamsCount];
//        _placement[i] = new uint8[_sizeTeam];
//        for (uint8 j = 0; j < _sizeTeam; ++j)
//            _teams[i][j] = Unit();
//    }
}

BattleController::~BattleController()
{
    delete[] _units;
    delete[] _speedList;

//    for (uint8 i = 0; i < _teamsCount; ++i)
//    {
//        delete[] _teams[i];
//        delete[] _placement[i];
//    }
//    delete[] _teams;
//    delete[] _placement;
}

void BattleController::gameTick()
{
    signalActive(Signal::BeforeGloabalTick);
    for (uint8 i = 0; i < _teamsCount * _sizeTeam; i++)
        _units[_speedList[i]].gameTick();
    signalActive(Signal::AfterGloabalTick);
}

Unit& BattleController::getUnit(uint8 idUnit)
{
    return _units[idUnit];
}

void BattleController::signalActive(const Signal signalType, SignalStruct& signalStruct)
{
    if (signalsCyclesCount++ < SIGNAL_CYCLES_MAX)
        actionBuff(signalType, signalStruct);

    if (!--signalsCyclesCount /* &&  _needRemoveBuffFromList*/)
        removeInActiveBuff();
}

void BattleController::sortSpeedList()
{
    for (uint8 i = 0; i < _teamsCount * _sizeTeam - 1; ++i)
        for (uint8 j = i + 1; j < _teamsCount * _sizeTeam; ++j)
            if (Unit::isFaster(_units[_speedList[i]], _units[_speedList[j]]))
            {
                uint8 s = _speedList[j];
                _speedList[j] = _speedList[i];
                _speedList[i] = s;
            }
}

void BattleController::actionBuff(const Signal signalType, SignalStruct& signalStruct)
{
    for (auto it = _activeEffects.begin(); it != _activeEffects.end(); it++)
        it->action(signalType, signalStruct);
}

void BattleController::removeInActiveBuff()
{
    for (auto it = _activeEffects.begin(); it != _activeEffects.end();)
    {
        if (!it->isActive())
            it = _activeEffects.erase(it);
        else
            it++;
    }
}
