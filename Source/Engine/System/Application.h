#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/System/Window.h>
#include <Engine/Base/InputArray.h>
#include <Engine/GUI/Console.h>

class Application
{
    public:
        Window window;
        InputArray input;
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

extern Application* mainApp;
extern const char* mainPath;

#endif // APPLICATION_H
