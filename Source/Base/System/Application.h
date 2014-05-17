#ifndef APPLICATION_H
#define APPLICATION_H
#include <Base/System/Window.h>
#include <Base/System/InputArray.h>

struct GameObjects;

class Application
{
    private:
        Window appWindow;
        InputArray appInput;
        GameObjects* gameObjects;
        bool isRunning;

        void appInit();
        void appUpdate();
        void pollInput();

    public:
        Application(int argc, char** argv);
        Application(const Application& other) = delete;
        ~Application();
        int run();
        void quit();
        const Window& window() const;
        const InputArray& input() const;

};

extern Application* mainApp;

#endif // APPLICATION_H
