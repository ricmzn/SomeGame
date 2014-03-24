#include <QApplication>
#include "ToolWindow.h"

extern "C"
{
    int main(int argc, char** argv)
    {
        QApplication app(argc, argv);
        ToolWindow window;
        window.show();
        return app.exec();
    }
}
