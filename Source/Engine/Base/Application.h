#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Base/Entity.h>
#include <Engine/Base/XML/Document.h>
#include <Engine/System/Profiling.h>
#include <Engine/System/Window.h>
#include <Engine/System/Input.h>

namespace Base {
class api_public Application
{
    protected:
        virtual void initialize()   = 0;
        virtual void finalize()     = 0;
        virtual void loop()         = 0;

        Application(const Application& other) = delete;
    public:
        Application(int argc, char** argv);
        virtual ~Application();

        int run();
        void quit();

        System::ApplicationProfiler profiler;
        Base::XML::Document config;
        Base::Entity* rootEntity;
        System::Window window;
        System::Input input;
        Tick frameStart, frameEnd;
        float deltaTime;

    private:
        bool isRunning;
        void pollInput();
    };

    extern api_public Application* activeApplication;
    extern api_public const char*  applicationPath;
}

#endif // APPLICATION_H
