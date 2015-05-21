#include "Window.h"
#include <SDL2/SDL.h>
#include <Engine/Render/API.h>
#include <Engine/Base/Exceptions.h>
#include <cstdio>
using namespace System;

Window::Window(const char* title, int width, int height, WindowMode mode, int vsync)
    : width(width),
      height(height),
      vsync(vsync),
      mode(mode),
      aspectRatio(float(width)/float(height)),
      visible(false)
{
    SDL_Init(SDL_INIT_VIDEO);
    handle = SDL_CreateWindow(title, 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

    glContext = nullptr;
    // First try
    if(!glContext) {
        glContext = Render::initializeContext(handle, 4, 4);
    }
    // Second try...
    if(!glContext) {
        glContext = Render::initializeContext(handle, 3, 3);
    }
    // Give up
    if(!glContext) {
        throw GenericError("Failed to initialize an OpenGL context\n"
                           "Try updating your video driver to its latest version");
    }

    // Output some information about the renderer
    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    // And set up some useful things
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Window::Window(const char* title, int width, int height, int mode, int vsync)
    : Window(title, width, height, (WindowMode)mode, vsync)
{}

Window::~Window()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(handle);
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

float Window::getAspectRatio() const
{
    return aspectRatio;
}

bool Window::isVisible() const
{
    return visible;
}

void Window::setVisible(bool visible)
{
    this->visible = visible;
    SDL_HideWindow(handle);
    if(!visible) {
        return;
    }
    SDL_GL_SetSwapInterval(vsync);
    SDL_SetWindowSize(handle, width, height);
    SDL_SetWindowPosition(handle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    switch(mode) {
        default:
            printf("Unsupported mode: %d\n", mode);
        case WindowMode::WINDOWED:
            SDL_SetWindowBordered(handle, SDL_TRUE);
            SDL_SetWindowFullscreen(handle, SDL_FALSE);
            break;
        case WindowMode::BORDERLESS:
            SDL_SetWindowBordered(handle, SDL_FALSE);
            SDL_SetWindowFullscreen(handle, SDL_FALSE);
            break;
        case WindowMode::FULLSCREEN:
            SDL_SetWindowFullscreen(handle, SDL_WINDOW_FULLSCREEN);
            break;
        case WindowMode::DESKTOP: {
            SDL_DisplayMode displayMode;
            SDL_GetDesktopDisplayMode(0, &displayMode);
            SDL_SetWindowDisplayMode(handle, &displayMode);
            SDL_SetWindowFullscreen(handle, SDL_WINDOW_FULLSCREEN_DESKTOP);
            width = displayMode.w;
            height = displayMode.h;
            break;
        }
    }
    SDL_SetRelativeMouseMode(SDL_TRUE);
    glViewport(0, 0, width, height);
    SDL_ShowWindow(handle);
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    SDL_GL_SwapWindow(handle);
}

const SDL_Event& Window::getEvents()
{
    SDL_PollEvent(&events);
    return events;
}
