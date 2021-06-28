#ifndef SIGNALTYPE_H
#define SIGNALTYPE_H

#include "defines.h"
#include <limits>

enum Signal : int
{
    None                    = 0x0000000,
    BeforeDmgGetting        = 0x0000001,
    Death                   = 0x0000002,
    AfterDmgGetting         = 0x0000004,

    BeforeHpGetting         = 0x0000008,
    AfterHpGetting          = 0x000000F,

    BeforeHealGetting       = 0x0000010,
    OverHealGetting         = 0x0000020,
    AfterHealGetting        = 0x0000040,

    BeforeDefenseGetting    = 0x0000080,
    AfterDefenseGetting     = 0x00000F0,

    BeforeGloabalTick       = 0x0000100,
    BeforeSpGetting         = 0x0000200,
    OverSpGetting           = 0x0000400,
    AfterSpGetting          = 0x0000800,
    AfterGloabalTick        = 0x0000F00,


    All                     = 0xFFFFFFF
};

static stat invalidStat = std::numeric_limits<stat>::min();
struct SignalStruct
{
    SignalStruct() :
        idTarget(INVALID_ID),
        idOwner(INVALID_ID),
        data(invalidStat)
    {
    }

    SignalStruct(uint8 idT, uint8 idO, stat& d) :
        idTarget(idT),
        idOwner(idO),
        data(d)
    {
    }

    uint8 idTarget;
    uint8 idOwner;

    stat& data;
};

static SignalStruct invalidSignalStruct;


#endif // SIGNALTYPE_H
