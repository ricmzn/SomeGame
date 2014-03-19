#ifndef WINDOW_H
#define WINDOW_H
#include <Base/SharedTypes.h>

enum WindowFlags
{
    WINDOWED        = 0x0,
    NO_BORDER       = 0x1,
    FULLSCREEN      = 0x2,
    RESIZABLE       = 0x4
};

class Window
{
    private:
        void* native_handle;
    public:
        Window(const String& title, int width, int height, int refresh = 0, int flags = 0);
        ~Window(){}
};

#endif // WINDOW_H
