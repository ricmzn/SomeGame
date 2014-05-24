#ifndef APPLICATION_H
#define APPLICATION_H
#include <Base/System/Window.h>
#include <Base/System/InputArray.h>
#include <GUI/Console.h>

struct GameObjects;

class Application
{
    private:
        Window appWindow;
        InputArray appInput;
        GameObjects* gameObjects;
        Console mainConsole;
        bool isRunning;

        void pollInput();
        void initialize();
        void loopBody();

    public:
        Application(int argc, char** argv);
        Application(const Application& other) = delete;
        ~Application();
        int run();
        void quit();
        const Window& window() const;
        const InputArray& input() const;
        Console& console();

        float deltaTime;
};

extern Application* mainApp;

#endif // APPLICATION_H
