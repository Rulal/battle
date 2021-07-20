#ifndef BUFFACTION_H
#define BUFFACTION_H

#include "signaltype.h"

#include <string>

class BattleController;

class BuffAction
{

protected:
    struct Params
    {
        BattleController* battleController;
        uint8 owner = INVALID_ID;
        uint8 carrier = INVALID_ID;

        Signal signalType;
        Signal subscribes;
        int settings;

        uint16 stacks;
        int time;

        std::string action;
        std::string actionAfterDead;
    };

    void activateString(bool dead);

private:
    Params _params;

};

#endif // BUFFACTION_H
