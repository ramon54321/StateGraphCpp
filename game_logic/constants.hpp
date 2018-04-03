#pragma once
#include <climits>

enum Events
{
    TICK = 1 << 0,
    NETWORK = 1 << 1,
    ALL = UINT_MAX
};