#ifndef SHADERGLWIDGET_H
#define SHADERGLWIDGET_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../Source/cube.cpp"

class ShaderGLWidget : public QGLWidget, private QOpenGLFunctions_4_0_Core
{
        Q_OBJECT

    public:
        ShaderGLWidget(const QGLFormat &format, QWidget *parent = 0) :
            QGLWidget(format, parent)
        {
            this->setAutoBufferSwap(true);
            offset = glm::vec4(0);
            setFocusPolicy(Qt::ClickFocus);
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(update()));
            timer->setInterval(33);
            timer->start();
        }

    private:
        QTimer* timer;
        QOpenGLShaderProgram shader;
        GLuint mvpLocation;
        GLuint vbo, vao;
        glm::mat4 model, view, projection;
        glm::vec4 offset;
        void initializeGL()
        {
            initializeOpenGLFunctions();
            shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "../Data/Shaders/UnlitGeneric.vert");
            shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "../Data/Shaders/UnlitGeneric.frag");
            shader.link();
            qDebug() << "GL Version:" << (const char*)glGetString(GL_VERSION);

            glClearColor(0, 0, 0, 1);
            glClearDepth(1);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CW);
            glViewport(0, 0, width(), height());

            // Set up uniforms for the shader
            mvpLocation = glGetUniformLocation(shader.programId(), "MVP");

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
            qDebug() << "New size:" << w << 'x' << h;
        }
        void paintGL()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            const float& x = offset.x;
            const float& y = offset.y;
            const float& z = offset.z;

            // Matrices
            model = glm::mat4(1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              x, y, z, 1);

            view = glm::lookAt(glm::vec3(0, 0, 2),
                               glm::vec3(0, 0, 0),
                               glm::vec3(0, 1, 0));

            projection = glm::perspective(60.0, (double)width()/(double)height(), 0.01, 10000.0);

            glm::mat4 modelViewProjection = projection * view * model;

            // Set the shader program
            glUseProgram(shader.programId());
            glUniformMatrix4fv(mvpLocation, 1, false, &modelViewProjection[0][0]);
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
        void keyPressEvent(QKeyEvent* event)
        {
            switch (event->key())
            {
                case Qt::Key_Left:
                    offset.x -= 0.02;
                    break;
                case Qt::Key_Right:
                    offset.x += 0.02;
                    break;
                case Qt::Key_Down:
                    offset.y -= 0.02;
                    break;
                case Qt::Key_Up:
                    offset.y += 0.02;
                    break;
                default:
                    event->ignore();
                    break;
            }
        }
};

#endif // SHADERGLWIDGET_H
