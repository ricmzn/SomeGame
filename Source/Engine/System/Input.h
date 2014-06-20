#ifndef WINDOWINPUT_H
#define WINDOWINPUT_H
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

namespace System
{
    class Input
    {
    public:
        struct {
            int keys[SDL_NUM_SCANCODES] = {0};
            int operator[] (const int& code) const {return keys[code] == 1;}
        }
        keyPressed,
        keyDown,
        keyUp;

        struct {
            int left    = 0;
            int right   = 0;
            int xrel    = 0;
            int yrel    = 0;
            int x       = 0;
            int y       = 0;
        } mouse;
    };
}

#endif // WINDOWINPUT_H
