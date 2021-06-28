#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "defines.h"

struct Owner
{
    uint8 id;
    uint8 spell_id;
};


class Effect
{
    enum TypeEffect : int
    {
        Unknow = 0,
        Phisical,
        Magical,
        Holy,
        Natural
    };

    int value;
    TypeEffect typeEffect;
    Owner owner;
};

//struct Damage
//{
//    enum DamageType
//    {
//        Phisical,
//        Magical
//    };

//    int value;
//    DamageType type;
//    Owner owner;
//};

//struct Heal
//{
//    enum HealType
//    {

//    };

//    int value;
//    HealType type;
//    Owner owner;
//};


#endif // STRUCTURES_H
