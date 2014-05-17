#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

class Window
{
    private:
        SDL_GLContext glContext;
        SDL_Window* windowHandle;
        SDL_Event windowEvents;
        const char* title;
        int width, height;
    public:
        Window(const char* title, int width, int height);
        int getWidth() const;
        int getHeight() const;
        void makeVisible();
        void clear();
        void display();
        const SDL_Event& getEvents();
};

#endif // WINDOW_H
