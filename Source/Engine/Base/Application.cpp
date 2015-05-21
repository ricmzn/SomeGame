#include "Application.h"
#include <Engine/Base/Exceptions.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <ctime>
using namespace Base;

Application* Base::activeApplication = nullptr;
const char*  Base::applicationPath = nullptr;

Application::Application(int argc, char** argv)
    : config("Config/System.xml"),
      window("SomeGame (SDL)",
            config.getNode("Renderer/Width").asInteger(640),
            config.getNode("Renderer/Height").asInteger(480),
            config.getNode("Renderer/Mode").asInteger(0),
            config.getNode("Renderer/VSync").asInteger(1)),
      frameStart(0), frameEnd(0), deltaTime(0.f),
      isRunning(false)
{
    if(activeApplication) {
        throw GenericError("Only one instance of Application is allowed!");
    }

    (void)argc;
    activeApplication = this;
    applicationPath = argv[0];

    rootEntity = new Base::Entity();
    srand(time(NULL));
}

Application::~Application()
{
    delete rootEntity;
    activeApplication = nullptr;
}

int Application::run()
{
    static int frameCounter = 0;
    if(isRunning) {
        return -1;
    } else {
        isRunning = true;
        this->initialize();
        window.setVisible(true);
        while(isRunning) {
            ScopeProfiler outer(this->profiler, "entire frame");
            // Main loop (minus refresh and profiling)
            if(true) {
                ScopeProfiler sp(this->profiler, "main loop");
                frameStart = SDL_GetTicks();
                window.clear();
                this->pollInput();
                this->loop();
            }
            window.update();
            frameEnd = SDL_GetTicks();
            deltaTime = (frameEnd - frameStart) / 1000.f;

            // Print frame time information
            if(false) {
                printf("Frame %d\n", frameCounter);
                printf("  This frame:\n");
                profiler.forEachFrame([](StringRef key, Tick value) {
                    printf("    %s: %lldus (%dms)\n", key.c_str(), value/1000, int(value/1000000));
                });
                printf("  Total elapsed:\n");
                profiler.forEachTotal([](StringRef key, Tick value) {
                    printf("    %s: %lldus (%dms)\n", key.c_str(), value/1000, int(value/1000000));
                });
                printf("\n");
                frameCounter++;
            }
            profiler.clearCurrentFrame();
        }
        this->finalize();
    }
    return 0;
}

void Application::quit()
{
    isRunning = false;
}

void Application::pollInput()
{
    // TODO: Make so keyPressed only triggers once per key press
    input.mouse.xrel = 0;
    input.mouse.yrel = 0;

    for(int& key : input.keyDown.keys) {
        if(key == 1) {
            key = -1;
        }
    }

    if(!window.isVisible()) {
        return;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        const SDL_Scancode key = event.key.keysym.scancode;
        if(event.type == SDL_QUIT or
          (event.type == SDL_KEYDOWN and event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
            this->quit();
            break;
        }

        if(event.type == SDL_KEYDOWN) {
            input.keyPressed.keys[key] = 1;
            if(input.keyDown.keys[key] == 0) {
                input.keyDown.keys[key] = 1;
            }
        } else if(event.type == SDL_KEYUP) {
            input.keyPressed.keys[key] = 0;
            if(input.keyDown.keys[key] < 0) {
                input.keyDown.keys[key] = 0;
            }
        }
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) input.mouse.left = true;
            if (event.button.button == SDL_BUTTON_RIGHT) input.mouse.right = true;
        } else if(event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) input.mouse.left = false;
            if (event.button.button == SDL_BUTTON_RIGHT) input.mouse.right = false;
        }
        if(event.type == SDL_MOUSEMOTION) {
            input.mouse.xrel = event.motion.xrel;
            input.mouse.yrel = event.motion.yrel;
            input.mouse.x = event.motion.x;
            input.mouse.y = event.motion.y;
        }
    }
}
