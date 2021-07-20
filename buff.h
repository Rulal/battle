#ifndef EFFECT_H
#define EFFECT_H


#include "buffaction.h"

class BattleController;

class Buff : public BuffAction
{
    enum Settings : uint8
    {
        None            = 0x00,
        IsActive        = 0x01,
        Invisibility    = 0x02,
        OverTime        = 0x04,
        Dispels1        = 0x08,
        Dispels2        = 0x0F,
        Dispels3        = Dispels1 | Dispels2,

        //= 0x10,
        //= 0x20,
        //= 0x40,
        //= 0x80,
        //= 0xF0,
    };

public:

    Buff(BattleController* battleController, uint8 idBuff, uint8 owner, uint8 carrier);
    ~Buff();

    bool isActive() const;
    void action(const Signal signalType, SignalStruct& signalStruct);
    bool dispel(uint8 level);
    const Buff::Params& getParams() const;

//    const std::string& getActionString() const;
//    const std::string& getAfterDeadActionString() const;


private:
    void init(uint8 id);
    void actionAfterDead();
    bool isSubscribe(const Signal signalType) const;
    uint8 getNeededDispelLevel() const;
    void setInActive();

    Params _params;


public:


};

#endif // EFFECT_H
