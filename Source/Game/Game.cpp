#include "Game.h"
#include <Engine/Base/BinaryTexture.h>
#include <Engine/Filesystem/File.h>
#include <SDL2/SDL.h>
#include <cstring>
extern Camera* mainCamera;

void Game::initialize()
{
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    PlayerController* player = new PlayerController();
    Universe::Manager* universe = new Universe::Manager(player);
    camera = new Render::Camera(60.f, window.getAspectRatio(), 1, 100000);
    rootEntity->addChild(player);
    rootEntity->addChild(universe);
    player->addChild(camera);
}

void Game::finalize()
{
    puts("Quitting...");
}

void Game::loop()
{
    window.clear();
    rootEntity->updateChildren(camera);
    window.display();
}

Game::Game(int argc, char** argv)
    : Application(argc, argv)
{}
