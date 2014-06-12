#ifndef WINDOWINPUT_H
#define WINDOWINPUT_H
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

namespace System
{
    class Input
    {
    public:
        // TODO stop being a hipster and use proper functions instead of operator[]
        struct {
            int keys[SDL_NUM_SCANCODES];
            int operator[] (const int& code) const {return keys[code] == 1;}
        }
        keyPressed,
        keyDown,
        keyUp;

        struct {
            int left;
            int right;
            int xrel;
            int yrel;
            int x;
            int y;
        } mouse;
    };
}

#endif // WINDOWINPUT_H
