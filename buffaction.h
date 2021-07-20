#ifndef BUFFACTION_H
#define BUFFACTION_H

#include "signaltype.h"

#include <string>

class BattleController;

class BuffAction
{
public:
    bool isValidate() const;

protected:
    struct Params
    {
        BattleController* battleController = nullptr;
        uint8 owner = INVALID_ID_8;
        uint8 carrier = INVALID_ID_8;

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
