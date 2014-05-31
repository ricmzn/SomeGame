#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/System/Window.h>
#include <Engine/Base/InputArray.h>
#include <Engine/GUI/Console.h>

class Application
{
    protected:
        Window appWindow;
        InputArray appInput;
        Console appConsole;

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
        const Window& window() const;
        const InputArray& input() const;
        Console& console();

        float deltaTime;
};

extern Application* mainApp;
extern const char* mainPath;

#endif // APPLICATION_H
