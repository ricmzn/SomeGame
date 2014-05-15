#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#ifdef __WIN32__
    #define WIN32_MEAN_AND_LEAN
    #include <windows.h>
    #define MessageBoxError(title, message)\
            (MessageBoxA(0, message, title, MB_ICONERROR | MB_OK))
    #define MessageBoxWarning(title, message)\
            (MessageBoxA(0, message, title, MB_ICONWARNING | MB_OK))
    #define MessageBoxYesNo(title, message)\
            (MessageBoxA(0, message, title, MB_ICONQUESTION | MB_YESNO) == IDYES)
    #undef WIN32_MEAN_AND_LEAN
#else
    #include <SDL2/SDL_messagebox.h>
    #define MessageBoxError(title, message)\
            (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL))
    #define MessageBoxWarning(title, message)\
            (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, message, NULL))
    #define MessageBoxYesNo(title, message)\
            (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", "SDL Yes/No dialog not implemented", NULL) == 1)
#endif

#endif // MESSAGEBOX_H
