#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <Engine/System/Macros.h>

namespace System {
class api_public Messagebox
{
    private:
        Messagebox();
    public:
        enum class Option
        {
            Cancel,
            Ok,
            Yes = Ok,
            No = Cancel
        };

        static Option Error            (const char* title, const char* message);
        static Option Warning          (const char* title, const char* message);
        static Option YesNo            (const char* title, const char* message);
};
}

#endif // MESSAGEBOX_H
