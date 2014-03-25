#ifndef TOOLLAUNCHER_H
#define TOOLLAUNCHER_H

#include <QMainWindow>
#include "ResourceConverter.h"
#include "ShaderViewer.h"

namespace Ui {
    class ToolLauncher;
}

class ToolsWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit ToolsWindow(QWidget *parent = 0);
        ~ToolsWindow();

    private:
        Ui::ToolLauncher *ui;
};

#endif // TOOLLAUNCHER_H
