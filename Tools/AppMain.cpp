#include <QApplication>
#include "ToolsWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ToolsWindow window;
    window.show();
    return app.exec();
}
