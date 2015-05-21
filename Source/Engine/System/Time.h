#ifndef TIME_H
#define TIME_H
#include <Engine/Base/Types/Shared.h>
#include <Engine/System/Macros.h>

namespace System {
class api_public Time
{
    private:
        Time();
    public:
        static Tick getNanoseconds();
};
}

#endif // TIME_H
