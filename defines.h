#ifndef DEFINES_H
#define DEFINES_H

#define BATTLEGROUND_ID 254
#define INVALID_ID 255
#define SIGNAL_CYCLES_MAX 100

using uint8 = unsigned char;
using uint16 = unsigned short;
using stat = int;

static bool idIsValid(uint8 id)
{
    return id != INVALID_ID;
}

#endif // DEFINES_H
