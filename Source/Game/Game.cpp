#include "Game.h"
#include <Engine/Filesystem/File.h>
#include <SDL2/SDL.h>
#include <cstring>

GameObjects::GameObjects()
    : skybox("Meshes/starcube.mdl", Vec3(0, 0, 0))
{
    loadBitmapTextSDL(NULL, "Fonts/curses_640x300.bmp", &text);

    File skyTex("Textures/stars.bmp");
    SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(skyTex.data(), skyTex.size()), 1);
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

void Game::pollInput()
{
    appInput.mouse.xrel = 0;
    appInput.mouse.yrel = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT or
           (event.type == SDL_KEYDOWN and event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
        {
            this->quit();
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

void Game::initialize()
{
    Filesystem::setRootPath("../Data");
    memset(&appInput, 0, sizeof(InputArray));
    gameObjects = new GameObjects();
}

void Game::finalize()
{
    delete gameObjects;
}

void Game::loopBody()
{
    appWindow.clear();
    gameObjects->text.setString("nil");
    gameObjects->player.update(deltaTime);
    gameObjects->skybox.draw(gameObjects->skyCam);
    gameObjects->text.draw(0, 0);
    appWindow.display();
}

Game::Game(int argc, char **argv)
    : Application(argc, argv)
{}
