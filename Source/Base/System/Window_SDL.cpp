#include "Window.h"
#include <SDL2/SDL.h>
#include <cstdio>

Window::Window(const String& title, int width, int height, int refresh, int flags)
{
    SDL_Window* window = SDL_CreateWindow(NULL, 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowTitle(window, title.c_str());
    SDL_SetWindowSize(window, width, height);
    if (flags & NO_BORDER)
    {
        SDL_SetWindowBordered(window, SDL_FALSE);
    }
    SDL_DestroyWindow(window);
}
