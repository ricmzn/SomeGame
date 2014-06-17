#ifndef GAMEAPP_H
#define GAMEAPP_H
#include <Engine/System/Application.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/StaticModel.h>
#include <Game/Universe/Manager.h>
#include <Engine/GUI/BitmapText.h>

struct GameObjects
{
    BitmapText text;
    PlayerController player;
    Universe::Manager universe;
    Camera* camera;
    Camera* skyCam;
    GameObjects();
};

class Game : public System::Application
{
    protected:
        GameObjects* gameObjects;
        virtual void initialize();
        virtual void finalize();
        virtual void loop();

    public:
        Game(int argc, char** argv);
};

#endif // GAMEAPP_H
