#include "buff.h"

Buff::Buff(BattleController* battleController, uint8 idBuff, uint8 owner, uint8 carrier)
{
    _params.battleController = battleController;
    _params.owner = owner;
    _params.carrier = carrier;
    init(idBuff);
}

Buff::~Buff()
{
}

bool Buff::isActive() const
{
    return _params.settings & Settings::IsActive;
}

void Buff::action(const Signal signalType, SignalStruct& signalStruct)
{
    if (!isActive())
        return;

    if (signalType == Signal::Death && signalStruct.idOwner == _params.carrier)
        setInActive();

    if (signalType == Signal::BeforeGloabalTick)
        if (_params.time-- <= 0)
            setInActive();

    if (!isSubscribe(signalType))
        return;

    activateString(false);
}

bool Buff::dispel(uint8 level)
{
    if (!isActive())
        return false;

    if (auto neededDispelLevel = getNeededDispelLevel())
    {
        if (level >= neededDispelLevel)
        {
            setInActive();
            actionAfterDead();
            return true;
        }
    }

    return false;
}

const Buff::Params& Buff::getParams() const
{
    return _params;
}

void Buff::init(uint8 id)
{
    if (!idIsValid(id))
        return;

    //TODO: загрузка из бд/контроллера парамметров баффа
}

void Buff::actionAfterDead()
{
    if (!isActive())
        return;

    activateString(false);
}

bool Buff::isSubscribe(const Signal signalType) const
{
    return _params.subscribes | signalType;
}

uint8 Buff::getNeededDispelLevel() const
{
    return _params.settings >> 2 & 0x3;
}

void Buff::setInActive()
{
    _params.settings |= Settings::IsActive;
}
