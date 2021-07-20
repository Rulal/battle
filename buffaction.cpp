#include "buffaction.h"
#include "buff.h"
#include "battlecontroller.h"
#include "unit.h"

bool BuffAction::isValidate() const
{
    return _params.battleController != nullptr;
}

void BuffAction::activateString(bool dead)
{
    uint8 target = _params.carrier;
    uint8 owner = _params.owner;
    stat buff1 = 0;
    std::string& str = dead ? _params.actionAfterDead : _params.action;

    for (uint8 i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case 41:
        {
            _params.battleController->getUnit(target).gettingDMG(buff1, owner);
            break;
        }
        case 42:
        {
            _params.battleController->getUnit(target).gettingHeal(buff1, owner);
            break;
        }
        case 43:
        {
            _params.battleController->getUnit(target).gettingSP(buff1, owner);
            break;
        }
        case 44:
        {
            _params.battleController->getUnit(target).gettingHP(buff1, owner);
            break;
        }
        case 45:
        {
           target = _params.owner;
           break;
        }
        case 46:
        {
           target = _params.carrier;
           break;
        }
        case 47:
        {
           owner = _params.owner;
           break;
        }
        case 48:
        {
           owner = _params.carrier;
           break;
        }
        case 49:
        {
           owner = _params.carrier;
           break;
        }
        case 50:
        {
           buff1 = dataToValue<uint16>(str.data(), i + 1);
           i += sizeof(uint16);
           break;
        }
        default:
            break;
        }
    }
}
