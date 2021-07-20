#include "battlecontroller.h"
#include "unit.h"

BattleController::BattleController(uint8 teamsCount, uint8 sizeTeam) :
    _teamsCount(teamsCount),
    _sizeTeam(sizeTeam)
{
    _units = new Unit[_teamsCount * _sizeTeam];
    _speedList = new stat[_teamsCount * _sizeTeam];
    _userActions = new std::list<UserAction>[_teamsCount];

    for (uint8 i = 0; i < _teamsCount; i++)
    {
        for (uint8 j = 0; j < _sizeTeam; j++)
        {
            _units[i * _sizeTeam + j].init(i * _sizeTeam + j, i, j, this);
        }
    }
}

BattleController::~BattleController()
{
    delete[] _units;
    delete[] _speedList;
    delete[] _userActions;
}

void BattleController::gameTick()
{
    signalActive(Signal::BeforeGloabalTick);
    for (uint8 i = 0; i < _teamsCount * _sizeTeam; i++)
        _units[_speedList[i]].gameTick();
    signalActive(Signal::AfterGloabalTick);
}

void BattleController::trySpellCast()
{
    for (uint8 i = 0; i < _teamsCount * _sizeTeam; i++)
    {
        std::list<UserAction>& teamActions = _userActions[_speedList[i] / _sizeTeam];
        for (auto it = teamActions.begin(); it != teamActions.end();)
        {
            if (_speedList[i] == it->owner && _units[it->owner].activateSpell(it->spellId, it->target))
                it = teamActions.erase(it);
            else
                it++;
        }
    }
}

Unit& BattleController::getUnit(uint8 idUnit)
{
    return _units[idUnit];
}

void BattleController::addUserAction(UserAction action)
{
#ifdef STUPID_VALIDATE
   if  (action.owner >= _sizeTeam * _teamsCount)
       return;
#endif

    _userActions[action.owner / _sizeTeam].push_back(action);
    _userActions[action.owner / _sizeTeam].unique();
}

void BattleController::removeUserAction(UserAction action)
{
#ifdef STUPID_VALIDATE
   if  (action.owner >= _sizeTeam * _teamsCount)
       return;
#endif

    _userActions[action.owner / _sizeTeam].remove(action);
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
//    for (auto it = _activeEffects.begin(); it != _activeEffects.end(); it++)
//        it->action(signalType, signalStruct);
    for (auto& item : _activeEffects)
        item.action(signalType, signalStruct);
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

    sortSpeedList(); //static sort
                     //TO DO: dynamic sort
}
