#include "Window.h"
#include <SDL2/SDL.h>
#include <Engine/Render/API.h>

Window::Window(const char* title, int width, int height)
    : title(title),
      width(width),
      height(height)
{
    SDL_Init(SDL_INIT_VIDEO);

    // TODO automatic switch between 3.3 and 4.0
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // TODO adjustable MSAA settings
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    windowHandle = SDL_CreateWindow(title, 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(windowHandle);
    SDL_GL_SetSwapInterval(1);
    initializeContext();

    glViewport(0, 0, this->width, this->height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Window::~Window()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(windowHandle);
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

void Window::makeVisible()
{
    SDL_SetWindowSize(windowHandle, width, height);
    SDL_SetWindowPosition(windowHandle,
                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowWindow(windowHandle);
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::display()
{
    SDL_GL_SwapWindow(windowHandle);
}

const SDL_Event& Window::getEvents()
{
    SDL_PollEvent(&windowEvents);
    return windowEvents;
}
