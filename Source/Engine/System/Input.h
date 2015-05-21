#ifndef WINDOWINPUT_H
#define WINDOWINPUT_H
#include <Engine/System/Macros.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

namespace System {
class api_public Input
{
    public:
        class api_public KeyArray {
            public:
                int keys[SDL_NUM_SCANCODES];
                int operator[](const int& code) const;
                KeyArray();
        };

        KeyArray keyPressed;
        KeyArray keyDown;
        KeyArray keyUp;

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
