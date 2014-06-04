#include "Messagebox.h"
using namespace Messagebox;

#if defined(__WIN32__)
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

Option Messagebox::Error(const char* title, const char* message)
{
    MessageBoxA(NULL, message, title, MB_ICONERROR | MB_OK);
    return Option::Ok;
}

Option Messagebox::Warning(const char* title, const char* message)
{
    MessageBoxA(NULL, message, title, MB_ICONWARNING | MB_OK);
    return Option::Ok;
}

Option Messagebox::YesNo(const char* title, const char* message)
{
    switch(MessageBoxA(NULL, message, title, MB_ICONQUESTION | MB_YESNO))
    {
        case IDYES:
            return Option::Yes;
            break;
        case IDNO: default:
            return Option::No;
            break;
    }
}
#else // __WIN32__ not defined, try SDL
#include <SDL2/SDL_messagebox.h>

Option Messagebox::Error(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
    return Option::Ok;
}

Option Messagebox::Warning(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, message, NULL);
    return Option::Ok;
}

Option Messagebox::YesNo(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "SDL Yes/No dialog not implemented", NULL);
    return Option::Ok;
}
#endif
