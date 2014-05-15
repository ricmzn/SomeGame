#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <GUI/BitmapText.h>
#include <Base/Exceptions.h>
#include <Base/System/Messagebox.h>
#include <Base/Entity/MeshEntity.h>
#include <Entities/TerrainManager.h>
#include <Entities/PlayerController.h>
#include <Entities/StaticModel.h>
#include <ctime>

InputArray input;
int WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 600;
float deltaTime = 0.f;

int main(int argc, char** argv) try
{
    srand(time(NULL));
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

    BitmapText text;
    loadBitmapTextSDL(NULL, "Fonts/curses_640x300.bmp", &text);
    std::stringstream ticker;

    Camera* camera = new Camera(60.f, WINDOW_WIDTH/float(WINDOW_HEIGHT));
    Camera* skyCam = new Camera(60.f, WINDOW_WIDTH/float(WINDOW_HEIGHT));
    camera->setClip(1.0f, 10000.f);
    skyCam->setClip(1000.f, 1000000.f);
    PlayerController player(&input);
    player.addChild(camera);
    player.addChild(skyCam);

    SDL_ShowWindow(window);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool runGame = true, atmo = false;

    // Loading screen
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        text.setString("Loading...");
        text.draw(0.45, 0.5);
        SDL_GL_SwapWindow(window);
    }

    Texture2D skyTexture;
    StaticModel skybox("Meshes/starcube.mdl", Vec3(0, 0, 0));
    {
        File file("Textures/stars.bmp");
        SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(file.data(), file.size()), 0);
        skyTexture.upload(surf->pixels, GL_BGR, GL_UNSIGNED_BYTE, surf->w, surf->h);
        skybox.texture = (GLuint)skyTexture;
        skybox.scale = 32;
        SDL_FreeSurface(surf);
    }

    // Main loop
    while (runGame)
    {
        input.mouse.xrel = 0;
        input.mouse.yrel = 0;
        uint32_t start = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                input.keyPressed[event.key.keysym.scancode] = 1;
            }
            else if (event.type == SDL_KEYUP)
            {
                input.keyPressed[event.key.keysym.scancode] = 0;
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
        if (deltaTime > 1/50.f)
        {
            ticker << "deltaTime: " << deltaTime << "s - " << floor(1/deltaTime) << "fps";
        }
        else
        {
            ticker << "";
        }
        text.setString(ticker.str().c_str());
        player.update(deltaTime);
        skybox.draw(skyCam);
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
