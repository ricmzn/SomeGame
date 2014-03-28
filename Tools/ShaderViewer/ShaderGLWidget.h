#ifndef SHADERGLWIDGET_H
#define SHADERGLWIDGET_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "../../Source/cube.cpp"

class ShaderGLWidget : public QGLWidget, private QOpenGLFunctions_4_0_Core
{
        Q_OBJECT

    public:
        ShaderGLWidget(const QGLFormat &format, QWidget *parent = 0) :
            QGLWidget(format, parent)
        {
            this->setAutoBufferSwap(true);
            timer = new QTimer(this);
            this->connect(timer, SIGNAL(timeout()), this, SLOT(update()));
            timer->setInterval(33);
            timer->start();
        }

    private:
        QTimer* timer;
        QOpenGLShaderProgram shader;
        GLuint vbo, vao;
        QMatrix4x4 model, view, projection;
        void initializeGL()
        {
            initializeOpenGLFunctions();

            printf("OpenGL version: %s\nDisplay device: %s\nVendor: %s\n",
                   glGetString(GL_VERSION),
                   glGetString(GL_RENDERER),
                   glGetString(GL_VENDOR));
                   fflush(stdout);

            shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "../Data/Shaders/UnlitGeneric.vert");
            shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "../Data/Shaders/UnlitGeneric.frag");
            shader.link();

            glClearColor(0, 0, 0, 1);
            glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
            glViewport(0, 0, width(), height());

            // Generate a VBO and VAO
            glGenBuffers(1, &vbo);
            glGenVertexArrays(1, &vao);
            // Bind them
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindVertexArray(vao);
            // Set the buffer data
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
            // Enable the first two vertex attributes
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            // Attribute index, 4 values per position, inform they're floats, unknown, space between values, first value
            glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, 0);
            glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, (void*) (sizeof(vertexData) / 2));
            // And clean up
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        void resizeGL(int w, int h)
        {
            glViewport(0, 0, w, h);
        }
        void paintGL()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            static float rotation = 0;
            rotation += 2;

            // Matrices
            model.setToIdentity();
            model.rotate(rotation, QVector3D(0, 1, 0));

            view.setToIdentity();
            view.lookAt(QVector3D(0, 0, 2),
                        QVector3D(0, 0, 0),
                        QVector3D(0, 1, 0));

            projection.setToIdentity();
            projection.perspective(60.0, (double)width()/(double)height(), 0.01, 10000.0);

            QMatrix4x4 modelViewProjection = projection * view * model;

            // Set the shader program
            //glUniformMatrix4fv(mvpLocation, 1, false, &modelViewProjection(0, 0));
            shader.setUniformValue("MVP", modelViewProjection);
            shader.bind();
            // Bind the vertex array
            glBindVertexArray(vao);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            // Draw the values
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // And unbind the vertex array
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glBindVertexArray(0);
        }
};

#endif // SHADERGLWIDGET_H
