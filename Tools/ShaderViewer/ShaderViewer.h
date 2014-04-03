#ifndef SHADERVIEWER_H
#define SHADERVIEWER_H

#include <QWidget>
#include <ShaderViewer/ShaderGLWidget.h>
#include <QPushButton>
#include <QFileDialog>
#include <iostream>

namespace Ui {
    class ShaderViewer;
}

class ShaderViewer : public QWidget
{
        Q_OBJECT

    public:
        explicit ShaderViewer(QWidget *parent = 0);
        ~ShaderViewer();

    private slots:
        void on_modelSelector_clicked();

        void on_wireframeBox_stateChanged(int arg1);

        void fillUniformList();

    private:
        Ui::ShaderViewer *ui;
        ShaderGLWidget* glWidget;
};

#endif // SHADERVIEWER_H
