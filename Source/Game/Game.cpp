#include "Game.h"
#include <Engine/Base/BinaryTexture.h>
#include <Engine/Filesystem/File.h>
#include <SDL2/SDL.h>
#include <cstring>

GameObjects::GameObjects()
    : universe(player)
{
    loadBitmapTextSDL(NULL, "Fonts/curses_640x300.bmp", &text);

    float aspect = (float) System::ActiveApplication->window.getWidth()
                 / (float) System::ActiveApplication->window.getHeight();

    camera = new Camera(60.f, aspect);
    skyCam = new Camera(60.f, aspect);
    camera->setClip(1.0f, 10000.f);
    skyCam->setClip(1000.f, 1000000.f);
    player.addChild(camera);
    player.addChild(skyCam);
    universe.spawn();
}

void Game::initialize()
{
    Filesystem::setRootPath("../Data");
    memset(&input, 0, sizeof(System::Input));
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    gameObjects = new GameObjects();
}

void Game::finalize()
{
    delete gameObjects;
}

void Game::loop()
{
    window.clear();
    gameObjects->text.setString("nil");
    gameObjects->player.updateChildren();
    gameObjects->universe.updateChildren();
    gameObjects->universe.draw(gameObjects->skyCam);
    gameObjects->universe.draw(gameObjects->camera);
    gameObjects->text.draw(0, 0);
    window.display();
}

Game::Game(int argc, char** argv)
    : Application(argc, argv)
{}
