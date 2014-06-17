#include "Application.h"
#include <Engine/Base/Exceptions.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <ctime>
namespace System
{
    Application* ActiveApplication = nullptr;
    const char*  ApplicationPath = nullptr;
}
using namespace System;

Application::Application(int argc, char** argv)
    : window("SomeGame (SDL)", 1280, 720),
      isRunning(false),
      deltaTime(0.f)
{
    if (ActiveApplication) throw GenericError("Cannot create more than one Application");

    ActiveApplication = this;
    ApplicationPath = argv[0];

    srand(time(NULL));
}

Application::~Application()
{
    ActiveApplication = nullptr;
}

void Application::pollInput()
{
    // TODO correct keyPressed handling
    input.mouse.xrel = 0;
    input.mouse.yrel = 0;

    for (int& key : input.keyDown.keys)
    {
        if (key == 1)
        {
            key = -1;
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        const int& key = event.key.keysym.scancode;

        if (event.type == SDL_QUIT or
           (event.type == SDL_KEYDOWN and event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
        {
            this->quit();
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            input.keyPressed.keys[key] = 1;

            if (input.keyDown.keys[key] == 0)
            {
                input.keyDown.keys[key] = 1;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            input.keyPressed.keys[key] = 0;

            if (input.keyDown.keys[key] < 0)
            {
                input.keyDown.keys[key] = 0;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT) input.mouse.left = true;
            if (event.button.button == SDL_BUTTON_RIGHT) input.mouse.right = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT) input.mouse.left = false;
            if (event.button.button == SDL_BUTTON_RIGHT) input.mouse.right = false;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            input.mouse.xrel = event.motion.xrel;
            input.mouse.yrel = event.motion.yrel;
            input.mouse.x = event.motion.x;
            input.mouse.y = event.motion.y;
        }
    }
}

int Application::run()
{
    if (isRunning)
    {
        return -1;
    }
    else
    {
        isRunning = true;
        this->initialize();
        window.makeVisible();
        while(isRunning)
        {
            uint32_t start = SDL_GetTicks();
            this->pollInput();
            this->loop();
            deltaTime = (SDL_GetTicks() - start) / 1000.f;
        }
        this->finalize();
    }
    return 0;
}

void Application::quit()
{
    isRunning = false;
}
