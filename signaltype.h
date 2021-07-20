#ifndef SIGNALTYPE_H
#define SIGNALTYPE_H

#include "defines.h"
#include <limits>

enum Signal : int
{
    None                    = 0x0000000,

    UserActivate            = 0x0000001,

    BeforeDmgGetting        = 0x0000002,
    Death                   = 0x0000004,
    AfterDmgGetting         = 0x0000008,

    BeforeHpGetting         = 0x0000010,
    AfterHpGetting          = 0x0000020,

    BeforeHealGetting       = 0x0000040,
    OverHealGetting         = 0x0000080,
    AfterHealGetting        = 0x0000100,

    BeforeDefenseGetting    = 0x0000200,
    AfterDefenseGetting     = 0x0000400,

    BeforeGloabalTick       = 0x0000800,
    BeforeSpGetting         = 0x0001000,
    OverSpGetting           = 0x0002000,
    AfterSpGetting          = 0x0004000,
    AfterGloabalTick        = 0x0008000,

    BeforeActivateSpell     = 0x0010000,
    AfterActivateSpell      = 0x0020000,

    BeforeSpSpend           = 0x0040000,
    AfterSpSpend            = 0x0080000,

    All                     = 0xFFFFFFF
};

static stat invalidStat = std::numeric_limits<stat>::min();
struct SignalStruct
{
    SignalStruct() :
        idTarget(INVALID_ID_8),
        idOwner(INVALID_ID_8),
        data(invalidStat)
    {
    }

    SignalStruct(uint8 idTarget, uint8 idOwner, stat& d) :
        idTarget(idTarget),
        idOwner(idOwner),
        data(d)
    {
    }

    uint8 idTarget;
    uint8 idOwner;

    stat& data;
};

static SignalStruct invalidSignalStruct;


#endif // SIGNALTYPE_H
