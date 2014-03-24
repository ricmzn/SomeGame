#ifndef TOOLLAUNCHER_H
#define TOOLLAUNCHER_H

#include <QMainWindow>
#include "ResourceConverter.h"

namespace Ui {
    class ToolLauncher;
}

class ToolWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit ToolWindow(QWidget *parent = 0);
        ~ToolWindow();

    public slots:
        void runGame();

    private:
        Ui::ToolLauncher *ui;
};

#endif // TOOLLAUNCHER_H
