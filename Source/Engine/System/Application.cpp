#include "Application.h"
#include <Engine/Base/Exceptions.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <ctime>
Application* mainApp = nullptr;
const char* mainPath = nullptr;

Application::Application(int argc, char** argv)
    : appWindow("SomeGame (SDL)", 1280, 720),
      isRunning(false),
      deltaTime(0.f)
{
    if (mainApp) throw GenericError("Cannot create more than one Application!");

    mainApp = this;
    mainPath = argv[0];

    srand(time(NULL));
}

Application::~Application()
{
    mainApp = nullptr;
}

int Application::run()
{
    if (isRunning)
    {
        return -1;
    }
    else
    {
        this->initialize();
        isRunning = true;
        appWindow.makeVisible();
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

const Window& Application::window() const
{
    return appWindow;
}

const InputArray& Application::input() const
{
    return appInput;
}

Console& Application::console()
{
    return appConsole;
}
