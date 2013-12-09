#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>
#include <QMessageBox>
#include <GLFW/glfw3.h>
#include "videomode.h"

namespace Ui {
    class Launcher;
}

class Launcher : public QMainWindow
{
        Q_OBJECT

    public:
        explicit Launcher(QWidget *parent = 0);
        ~Launcher();

    private slots:
        void on_windowedBox_toggled(bool checked);

        void on_startButton_clicked();

        void on_resolutionBox_currentIndexChanged(int index);

    private:
        Ui::Launcher *ui;
        videoModeList modeList;
        bool windowed;
};

#endif // LAUNCHER_H
