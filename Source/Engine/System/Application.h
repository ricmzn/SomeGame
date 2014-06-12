#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/System/Window.h>
#include <Engine/System/Input.h>
#include <Engine/GUI/Console.h>

namespace System
{
    class Application
    {
    public:
        Window window;
        Input input;
        Console console;

    private:
        bool isRunning;
        virtual void pollInput()    = 0;
        virtual void initialize()   = 0;
        virtual void finalize()     = 0;
        virtual void loopBody()     = 0;

    public:
        Application(int argc, char** argv);
        Application(const Application& other) = delete;
        ~Application();
        int run();
        void quit();

        float deltaTime;
    };

    extern Application* ActiveApplication;
    extern const char*  ApplicationPath;
}

#endif // APPLICATION_H
