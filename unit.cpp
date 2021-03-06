#include "unit.h"
#include "signaltype.h"
#include "battlecontroller.h"


bool Unit::isFaster(const Unit& left, const Unit& right)
{
    if (left._speed != right._speed)
        return (left._speed < right._speed);

    if (left._curSP != right._curSP)
        return (left._curSP < right._curSP);

    if (left._maxSP != right._maxSP)
        return (left._maxSP < right._maxSP);

    if (left._curHP != right._curHP)
        return (left._curHP < right._curHP);

    if (left._maxHP != right._maxHP)
        return (left._maxHP < right._maxHP);

    if (left._defense != right._defense)
        return (left._defense > right._defense);

    if (left._damage != right._damage)
        return (left._damage < right._damage);

    if (left._place != right._place)
        return (left._place > right._place);

    if (left._team != right._team)
        return (left._team > right._team);

    return false;
}


Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::init(uint8 id, uint8 team, uint8 place, BattleController* battleController)
{
    _id = id;
    _team = team;
    _place = place;
    _battleController = battleController;
}

//void Unit::setBattleController(BattleController* battleController)
//{
//    _battleController = battleController;
//}

void Unit::gameTick()
{
    gettingSP(_speed, _id);
}

bool Unit::isDead() const
{
    return _curHP < 0;
}

bool Unit::activateSpell(uint8 spellId, uint8 target)
{
    if (spellId >= MAX_COUNT_SPELLS ||
            !spells[spellId].isValidate() ||
            _curSP < spells[spellId].getParams().stacks ||
            isDead())
        return false;

    stat invalidStat = 0;  // TO DO: optimization structurs count
    SignalStruct signalStruct1(target, _id, invalidStat);
    _battleController->signalActive(Signal::BeforeActivateSpell, signalStruct1);


    stat spCost = spells[spellId].getParams().stacks;
    SignalStruct signalStruct(_id, _id, spCost);
    _battleController->signalActive(Signal::BeforeSpSpend, signalStruct);
    _curSP -= spCost;
    _battleController->signalActive(Signal::AfterSpSpend, signalStruct);


    invalidStat = 0;
    SignalStruct signalStruct2(target, _id, invalidStat);
    spells[spellId].action(Signal::UserActivate, signalStruct2);

    invalidStat = 0;
    SignalStruct signalStruct3(target, _id, invalidStat);
    _battleController->signalActive(Signal::AfterActivateSpell, signalStruct3);

    return true;
}

void Unit::gettingSP(stat sp, uint8 idOwner)
{
    if (isDead())
        return;

    SignalStruct signalStruct(_id, idOwner, sp);

    _battleController->signalActive(Signal::BeforeSpGetting, signalStruct);
    _curSP += sp;

    if (_curSP - _maxSP >= 0)
        _battleController->signalActive(Signal::OverSpGetting, signalStruct);

    if (_curSP > _maxSP)
        _curSP = _maxSP;

    _battleController->signalActive(Signal::AfterSpGetting, signalStruct);
}

//void Unit::spendSP(stat sp, uint8 idOwner)
//{
//}

void Unit::gettingDMG(stat dmg, uint8 idOwner)
{
    if (dmg <= 0 || isDead())
        return;

    SignalStruct signalStruct(_id, idOwner, dmg);

    _battleController->signalActive(Signal::BeforeDmgGetting, signalStruct);
    _curHP -= dmg;
    _battleController->signalActive(Signal::AfterDmgGetting, signalStruct);

    if (_curHP <= 0)
        _battleController->signalActive(Signal::Death, signalStruct); // int overDMG = -_curHP;
}

void Unit::gettingHeal(stat heal, uint8 idOwner)
{
    if (heal <= 0 || isDead())
        return;

    SignalStruct signalStruct(_id, idOwner, heal);

    _battleController->signalActive(Signal::BeforeHealGetting, signalStruct);
    _curHP += heal;

    if (_curHP - _maxHP > 0)
        _battleController->signalActive(Signal::OverHealGetting, signalStruct);

    _battleController->signalActive(Signal::AfterSpGetting, signalStruct);

    if (_curHP > _maxHP)
        _curHP = _maxHP;
}


void Unit::gettingHP(stat hp, uint8 idOwner)
{
    if (isDead())
        return;

    SignalStruct signalStruct(_id, idOwner, hp);

    _battleController->signalActive(Signal::BeforeHpGetting, signalStruct);
    _maxHP += hp;

    if (hp > 0)
        _curHP += hp;

    if (_curHP > _maxHP)
        _curHP = _maxHP;

    _battleController->signalActive(Signal::AfterHpGetting, signalStruct);
}

