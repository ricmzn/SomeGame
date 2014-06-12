#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

namespace System
{
namespace Messagebox
{
    enum class Option
    {
        Cancel,
        Ok,
        Yes = Ok,
        No = Cancel
    };

    Option Error    (const char* title, const char* message);
    Option Warning  (const char* title, const char* message);
    Option YesNo    (const char* title, const char* message);
}
}

#endif // MESSAGEBOX_H
