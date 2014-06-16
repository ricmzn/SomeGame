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
            this->loopBody();
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
