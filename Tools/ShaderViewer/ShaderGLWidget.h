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
#include "../Source/cube.cpp"

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
            timer->setInterval(16);
            timer->start();
        }

    private:
        GLuint vao, vbo, ibo, fbo, prog, mvp_location;
        QTimer* timer;
        QOpenGLShaderProgram shader;
        QMatrix4x4 model, view, projection;
        void generateCube()
        {
            const float vertices[] = {
                -1, -1, -1, // 0 - Front bottom-left
                 1, -1, -1, // 1 - Front bottom-right
                 1,  1, -1, // 2 - Front upper-right
                -1,  1, -1, // 3 - Front upper-left
                -1,  1,  1, // 4 - Back upper-left
                 1,  1,  1, // 5 - Back upper-right
                 1, -1,  1, // 6 - Back bottom-right
                -1, -1,  1  // 7 - Back bottom-left
            };
            const unsigned indices[] = {
                0, 1, 2,   0, 2, 3, // Front
                1, 6, 5,   1, 5, 2, // Right
            };
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        }
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

            mvp_location = shader.uniformLocation("projectionMatrix");
            prog = shader.programId();

            glClearColor(0, 0, 0, 1);
            glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
//            glEnable(GL_CULL_FACE);
//            glCullFace(GL_BACK);
//            glFrontFace(GL_CCW);
            glViewport(0, 0, width(), height());

            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ibo);
            glGenFramebuffers(1, &fbo);

            glBindVertexArray(vao);
            glEnableVertexAttribArray(0);
            generateCube();
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
            rotation += 1;

            // Matrices
            model.setToIdentity();
            model.rotate(rotation, QVector3D(0, 1, 0));

            view.setToIdentity();
            view.lookAt(QVector3D(0, 0, 8),
                        QVector3D(0, 0, 0),
                        QVector3D(0, 1, 0));

            projection.setToIdentity();
            projection.perspective(60.0, (double)width()/(double)height(), 0.01, 10000.0);

            QMatrix4x4 modelViewProjection = projection * view * model;

            glUseProgram(prog);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &modelViewProjection(0, 0));
            glBindVertexArray(vao);
            // Draw the values
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glUseProgram(0);
        }
};

#endif // SHADERGLWIDGET_H
