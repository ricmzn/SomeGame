#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

namespace System
{
    class Window
    {
    private:
        SDL_GLContext glContext;
        SDL_Window* windowHandle;
        SDL_Event windowEvents;
        const char* title;
        int width, height;
        float aspectRatio;
    public:
        Window(const char* title, int width, int height);
        Window(const Window& other) = delete;
        ~Window();
        int getWidth() const;
        int getHeight() const;
        float getAspectRatio() const;
        void makeVisible();
        void clear();
        void display();
        const SDL_Event& getEvents();
    };
}

#endif // WINDOW_H
