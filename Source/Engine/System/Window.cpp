#include "Window.h"
#include <SDL2/SDL.h>
#include <Engine/Render/API.h>
#include <Engine/Base/Exceptions.h>
using namespace System;

Window::Window(const char* title, int width, int height)
    : title(title),
      width(width),
      height(height)
{
    SDL_Init(SDL_INIT_VIDEO);
    windowHandle = SDL_CreateWindow(title, 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

    // First try
    {
        glContext = Render::initializeContext(windowHandle, 4, 4);
    }
    // Second try...
    if (!glContext)
    {
        glContext = Render::initializeContext(windowHandle, 3, 3);
    }
    // Give up
    if (!glContext)
    {
        throw GenericError("Failed to initialize an OpenGL context\n"
                           "Try updating your video driver to its latest version");
    }

    // Output some information about the renderer
    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    // And set up some useful things
    SDL_GL_SetSwapInterval(1);
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
