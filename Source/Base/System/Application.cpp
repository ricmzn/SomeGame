#include "Application.h"
#include <Base/Filesystem/Filesystem.h>
#include <Base/Filesystem/File.h>
#include <Base/Exceptions.h>
#include <Entities/PlayerController.h>
#include <Entities/StaticModel.h>
#include <GUI/BitmapText.h>
#include <SDL2/SDL_timer.h>
#include <sstream>
#include <cstdlib>
#include <ctime>
Application* mainApp = nullptr;

struct GameObjects
{
    BitmapText text;
    PlayerController player;
    StaticModel skybox;
    Texture2D skyTexture;
    Camera* camera;
    Camera* skyCam;

    GameObjects()
        : skybox("Meshes/starcube.mdl", Vec3(0, 0, 0))
    {
        loadBitmapTextSDL(NULL, "Fonts/curses_640x300.bmp", &text);

        File skyTex("Textures/stars.bmp");
        SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(skyTex.data(), skyTex.size()), 0);
        skyTexture.upload(surf->pixels, GL_BGR, GL_UNSIGNED_BYTE, surf->w, surf->h);
        skybox.texture = (GLuint)skyTexture;
        skybox.scale = 32;
        SDL_FreeSurface(surf);
        skyTex.clear();

        float aspect = (float) mainApp->window().getWidth()
                     / (float) mainApp->window().getHeight();

        camera = new Camera(60.f, aspect);
        skyCam = new Camera(60.f, aspect);
        camera->setClip(1.0f, 10000.f);
        skyCam->setClip(1000.f, 1000000.f);
        player.addChild(camera);
        player.addChild(skyCam);
    }
};

/*----------*/
/* Private: */
/*----------*/

void Application::appInit()
{
    Filesystem::setRootPath("../Data");
    memset(&appInput, 0, sizeof(InputArray));
}

float deltaTime = 0;

void Application::appUpdate()
{
    std::stringstream ticker;
    uint32_t start = SDL_GetTicks();

    appWindow.clear();
    if (deltaTime > 1/50.f)
    {
        ticker << "deltaTime: " << deltaTime << "s - " << floor(1/deltaTime);
    }
    gameObjects->text.setString(ticker.str().c_str());
    gameObjects->player.update(deltaTime);
    gameObjects->skybox.draw(gameObjects->skyCam);
    gameObjects->text.draw(0, 0);
    appWindow.display();

    deltaTime = (SDL_GetTicks() - start)/1000.f;
}

void Application::pollInput()
{
    appInput.mouse.xrel = 0;
    appInput.mouse.yrel = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT or
           (event.type == SDL_KEYDOWN and event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
        {
            isRunning = false;
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            appInput.keyPressed[event.key.keysym.scancode] = 1;
        }
        else if (event.type == SDL_KEYUP)
        {
            appInput.keyPressed[event.key.keysym.scancode] = 0;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT) appInput.mouse.left = true;
            if (event.button.button == SDL_BUTTON_RIGHT) appInput.mouse.right = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT) appInput.mouse.left = false;
            if (event.button.button == SDL_BUTTON_RIGHT) appInput.mouse.right = false;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            appInput.mouse.xrel = event.motion.xrel;
            appInput.mouse.yrel = event.motion.yrel;
            appInput.mouse.x = event.motion.x;
            appInput.mouse.y = event.motion.y;
        }
    }
}

/*---------*/
/* Public: */
/*---------*/

Application::Application(int argc, char** argv)
    : appWindow("SomeGame (SDL)", 1024, 600),
      isRunning(false)
{
    if (mainApp) throw Exceptions::GenericError("Class Application is a singleton, "
                                                "creating more than one is not allowed!");
    srand(time(NULL));
    mainApp = this;
    gameObjects = nullptr;
}

Application::~Application()
{
    mainApp = nullptr;
    if (gameObjects)
    {
        delete gameObjects;
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
        appInit();
        isRunning = true;
        gameObjects = new GameObjects;
        appWindow.makeVisible();
        while(isRunning)
        {
            pollInput();
            appUpdate();
        }
        delete gameObjects;
        gameObjects = nullptr;
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
