#ifndef DEFINES_H
#define DEFINES_H

#define BATTLEGROUND_ID 254
#define INVALID_ID 255
#define SIGNAL_CYCLES_MAX 100

using uint8 = unsigned char;
using uint16 = unsigned short;
using stat = uint16;

static bool idIsValid(uint8 id)
{
    return id != INVALID_ID;
}


template <typename T>
static T dataToValue(const char* data, int offset = 0)
{
    return *(T*)(data + offset);
}

#endif // DEFINES_H
