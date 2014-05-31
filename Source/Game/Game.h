#ifndef GAMEAPP_H
#define GAMEAPP_H
#include <Engine/System/Application.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/StaticModel.h>
#include <Engine/GUI/BitmapText.h>

struct GameObjects
{
    BitmapText text;
    PlayerController player;
    StaticModel skybox;
    Texture2D skyTexture;
    Camera* camera;
    Camera* skyCam;
    GameObjects();
};

class Game : public Application
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
