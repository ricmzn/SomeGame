#ifndef SHADERVIEWER_H
#define SHADERVIEWER_H

#include <QWidget>
#include <ShaderViewer/ShaderGLWidget.h>

namespace Ui {
    class ShaderViewer;
}

class ShaderViewer : public QWidget
{
        Q_OBJECT

    public:
        explicit ShaderViewer(QWidget *parent = 0);
        ~ShaderViewer();

    private:
        Ui::ShaderViewer *ui;
};

#endif // SHADERVIEWER_H
