#ifndef GAMEAPP_H
#define GAMEAPP_H
#include <Engine/System/Application.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/StaticModel.h>
#include <Game/Universe/Manager.h>

class Game : public System::Application
{
    protected:
        virtual void initialize();
        virtual void finalize();
        virtual void loop();

        Camera* camera;

    public:
        Game(int argc, char** argv);
};

#endif // GAMEAPP_H
