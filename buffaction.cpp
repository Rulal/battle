#include "buffaction.h"
#include "buff.h"
#include "battlecontroller.h"
#include "unit.h"

void BuffAction::activateString(bool dead)
{
    uint8 target = _params.carrier;
    uint8 owner = _params.owner;
    stat buff1 = 0;
    std::string& str = dead ? _params.action : _params.action;

    for (uint8 i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case 0: ;
        case 1:
        {
            _params.battleController->getUnit(target).gettingDMG(buff1, owner);
        }
        case 2:
        {
            _params.battleController->getUnit(target).gettingHeal(buff1, owner);
        }
        case 3:
        {
            _params.battleController->getUnit(target).gettingSP(buff1, owner);
        }
        case 4:
        {
            _params.battleController->getUnit(target).gettingHP(buff1, owner);
        }
        case 5:
        {
           target = _params.owner;
        }
        case 6:
        {
           target = _params.carrier;
        }
        case 7:
        {
           owner = _params.owner;
        }
        case 8:
        {
           owner = _params.carrier;
        }
        case 9:
        {
           buff1 = dataToValue<uint16>(str.data(), i + 1);
           i += sizeof(uint16);
        }
        }
    }
}
