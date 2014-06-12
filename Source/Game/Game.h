#ifndef GAMEAPP_H
#define GAMEAPP_H
#include <Engine/System/Application.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/StaticModel.h>
#include <Game/Universe/UniverseManager.h>
#include <Engine/GUI/BitmapText.h>
using Universe::UniverseManager;

struct GameObjects
{
    BitmapText text;
    PlayerController player;
    Camera* camera;
    Camera* skyCam;
    UniverseManager universe;
    GameObjects();
};

class Game : public System::Application
{
    protected:
        GameObjects* gameObjects;
        virtual void pollInput();
        virtual void initialize();
        virtual void finalize();
        virtual void loopBody();

    public:
        Game(int argc, char** argv);
};

#endif // GAMEAPP_H
