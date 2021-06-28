#include "buffaction.h"
#include "buff.h"
#include "battlecontroller.h"
#include "unit.h"

void BuffAction::activateString(Buff& buff, bool dead)
{
    const Buff::Params& params = buff.getParams();
    uint8 target = params.carrier;
    uint8 owner = params.owner;
    stat buff1 = 0;

    for (const char symbol : dead ? params.action : params.action)
    {
        switch (symbol)
        {
        case 0: ;
        case 1:
        {
            params.battleController->getUnit(target).gettingDMG(buff1, owner);
        }
        case 2:
        {
            params.battleController->getUnit(target).gettingHeal(buff1, owner);
        }
        case 3:
        {
            params.battleController->getUnit(target).gettingSP(buff1, owner);
        }
        case 4:
        {
            params.battleController->getUnit(target).gettingHP(buff1, owner);
        }
        }
    }
}
