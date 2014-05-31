#ifndef INPUTARRAY_H
#define INPUTARRAY_H
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

struct InputArray
{
    int keyPressed[SDL_NUM_SCANCODES];
    struct {
        int left;
        int right;
        int xrel;
        int yrel;
        int x;
        int y;
    } mouse;
};

#endif // INPUTARRAY_H
