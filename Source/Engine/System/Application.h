#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Entity/RootEntity.h>
#include <Engine/System/Window.h>
#include <Engine/System/Input.h>
#include <Engine/GUI/Console.h>

namespace System
{
    class Application
    {
    public:
        Application(int argc, char** argv);
        Application(const Application& other) = delete;
        ~Application();

        Window window;
        Input input;
        Console console;
        RootEntity* rootEntity;

    private:
        bool isRunning;
        virtual void initialize()   = 0;
        virtual void finalize()     = 0;
        virtual void loop()         = 0;
        void pollInput();

    public:
        int run();
        void quit();
        float deltaTime;
    };

    extern Application* ActiveApplication;
    extern const char*  ApplicationPath;
}

#endif // APPLICATION_H
