#ifndef SHADERGLWIDGET_H
#define SHADERGLWIDGET_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <cube.cpp>

struct Uniform
{
    QString name;
    GLuint type;
    GLuint location;
};

class ShaderGLWidget : public QGLWidget, private QOpenGLFunctions_4_0_Core
{
        Q_OBJECT

    public:
        explicit ShaderGLWidget(const QGLFormat& format, QWidget* parent);
        QList<Uniform> getUniforms();
        void setWireframe(bool enable);

    signals:
        void contextReady();

    private:
        bool wireframe;
        GLuint vao, vbo, ibo, fbo, tex, prog, proj_location, color_location;
        QTimer* timer;
        QOpenGLShaderProgram shader;
        QMatrix4x4 model, view, projection;
        void generateCube();
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
};

#endif // SHADERGLWIDGET_H
