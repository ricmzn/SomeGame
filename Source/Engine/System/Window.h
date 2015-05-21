#ifndef WINDOW_H
#define WINDOW_H
#include <Engine/System/Macros.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

namespace System {
enum class WindowMode
{
    WINDOWED    = 0,
    FULLSCREEN  = 1,
    BORDERLESS  = 2,
    DESKTOP     = 3
};

class api_public Window
{
    private:
        SDL_GLContext glContext;
        SDL_Window* handle;
        SDL_Event events;
        int width, height, vsync;
        WindowMode mode;
        float aspectRatio;
        bool visible;
    public:
        Window(const char* title, int width, int height, WindowMode mode = WindowMode::WINDOWED, int vsync = 1);
        Window(const char* title, int width, int height, int mode, int vsync);
        Window(const Window& other) = delete;
        ~Window();
        int getWidth() const;
        int getHeight() const;
        float getAspectRatio() const;
        bool isVisible() const;
        void setVisible(bool visible);
        void clear();
        void update();
        const SDL_Event& getEvents();
};
}

#endif // WINDOW_H
