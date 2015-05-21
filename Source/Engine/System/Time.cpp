#include "Time.h"
#define NANOSECONDS_IN_SECOND 1000*1000*1000
using namespace System;

Tick Time::getNanoseconds()
{
    // Screw Windows, seriously
#ifdef _WIN32
    return 0;
#else
    static timespec clk;
    clock_gettime(CLOCK_MONOTONIC, &clk);
    return clk.tv_nsec + clk.tv_sec * NANOSECONDS_IN_SECOND;
#endif
}
