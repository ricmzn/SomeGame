#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <Base/Exceptions.h>
#include <Base/Messagebox.h>
#include <Render/BitmapText.h>
#include <Render/TestTerrain.h>
#include <glm/gtc/noise.hpp>
#include <ctime>

int keyPressed[SDL_NUM_SCANCODES] = {0};
int WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 600;
float deltaTime = 0.f;

int main(int argc, char** argv) try
{
    srand(time(NULL));
    Filesystem::initialize(argc, argv);
    Filesystem::setRootPath("../Data");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_Window* window = SDL_CreateWindow("SomeGame (SDL)",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);
    glInitializeContext();

    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    BitmapText text = loadBitmapTextSDL(NULL, "curses_640x300.bmp");
    std::stringstream ticker;

    TestTerrain terrain(32, 32, 5);
    terrain.generate(1.0, 1.5);

    SDL_ShowWindow(window);
    bool runGame = true;
    while (runGame)
    {
        uint32_t start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                keyPressed[event.key.keysym.scancode] = 1;
            }
            else if (event.type == SDL_KEYUP)
            {
                keyPressed[event.key.keysym.scancode] = 0;
            }

            if (event.type == SDL_QUIT or event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                runGame = false;
            }
//            if (event.type == SDL_WINDOWEVENT and event.window.event == SDL_WINDOWEVENT_RESIZED)
//            {
//                WINDOW_WIDTH = event.window.data1;
//                WINDOW_HEIGHT = event.window.data2;
//                glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ticker.str("");
        ticker << "deltaTime: " << deltaTime << "s";
        text.setString(ticker.str().c_str());
        terrain.draw();
        text.draw({0, 0});
        SDL_GL_SwapWindow(window);
        deltaTime = (SDL_GetTicks() - start)/1000.f;
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
catch (const BaseException& ex)
{
    MessageBoxError("Fatal Error", ex.message());
    std::cerr << ex.trace() << std::endl;
    return 1;
}
