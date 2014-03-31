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
        void on_modelSelector_activated(const QString &arg1);

        void on_materialSelector_clicked();

    private:
        Ui::ShaderViewer *ui;
};

#endif // SHADERVIEWER_H
