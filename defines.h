#ifndef DEFINES_H
#define DEFINES_H

//#define STUPID_VALIDATE 1

#define BATTLEGROUND_ID 254
#define INVALID_ID_8 255
#define INVALID_ID_16 65535
#define INVALID_ID_32 4294967295
#define SIGNAL_CYCLES_MAX 100


#define MAX_COUNT_SPELLS 5

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using stat = uint16;

static bool idIsValid(const uint8 id)
{
    return id != INVALID_ID_8;
}

template <typename T>
static T dataToValue(const char* data, int offset = 0)
{
    return *(T*)(data + offset);
}

#endif // DEFINES_H
