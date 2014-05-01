#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <Base/Exceptions.h>
#include <Base/Messagebox.h>
#include <Render/BitmapText.h>
#include <Entities/TerrainManager.h>
#include <Entities/PlayerController.h>
#include <ctime>

InputArray keys;
int WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 600;
float deltaTime = 0.f;

int main(int argc, char** argv) try
{
    srand(time(NULL));
    Filesystem::initialize(argc, argv);
    Filesystem::setRootPath("../Data");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
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
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n\n",
           glGetString(GL_VERSION),
           glGetString(GL_RENDERER),
           glGetString(GL_VENDOR));

    BitmapText text = loadBitmapTextSDL(NULL, "curses_640x300.bmp");
    std::stringstream ticker;

    Camera* camera = new Camera(60.f, WINDOW_WIDTH/float(WINDOW_HEIGHT));
    camera->setClip(1.0f, 32768.f);
    PlayerController player(&keys);
    player.addChild(camera);

    TerrainManager terrain(camera);
    terrain.setParams(5, 256, 256, 0.25, 2.0, 0.95, 8);

    SDL_ShowWindow(window);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool runGame = true, atmo = false;

    // Show a loading screen before generation
    if (true)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        text.setString("Generating terrain...");
        text.draw(0.2, 0.5);
        SDL_GL_SwapWindow(window);
    }

    // Sky color
    glClearColor(0x8B / 255.f,
                 0xD4 / 255.f,
                 0xFF / 255.f,
                 0xFF / 255.f);

    while (runGame)
    {
        keys.mouse.xrel = 0;
        keys.mouse.yrel = 0;
        uint32_t start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                keys.pressed[event.key.keysym.scancode] = 1;
            }
            else if (event.type == SDL_KEYUP)
            {
                keys.pressed[event.key.keysym.scancode] = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT) keys.mouse.left = true;
                if (event.button.button == SDL_BUTTON_RIGHT) keys.mouse.right = true;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT) keys.mouse.left = false;
                if (event.button.button == SDL_BUTTON_RIGHT) keys.mouse.right = false;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                keys.mouse.xrel = event.motion.xrel;
                keys.mouse.yrel = event.motion.yrel;
            }

            if (event.type == SDL_QUIT or event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                runGame = false;
            }

            if (event.type == SDL_KEYDOWN and event.key.keysym.scancode == SDL_SCANCODE_F)
            {
                if (atmo)
                {
                    player.setFlightMode(FlightMode::SPACE);
                    atmo = false;
                }
                else
                {
                    player.setFlightMode(FlightMode::ATMO);
                    atmo = true;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ticker.str("");
        ticker << "deltaTime: " << deltaTime << "s";
        text.setString(ticker.str().c_str());
        player.update(deltaTime);
        terrain.update(deltaTime);
        terrain.draw();
        text.draw(0, 0);
        SDL_GL_SwapWindow(window);
        deltaTime = (SDL_GetTicks() - start)/1000.f;
    }
    SDL_SetRelativeMouseMode(SDL_FALSE);
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
