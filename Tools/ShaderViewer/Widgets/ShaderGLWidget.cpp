#include "ShaderGLWidget.h"

ShaderGLWidget::ShaderGLWidget(const QGLFormat& format, QWidget* parent) :
    QGLWidget(format, parent)
{
    this->setAutoBufferSwap(true);
    timer = new QTimer(this);
    this->connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(16);
    timer->start();
    wireframe = false;
}

QList<Uniform> ShaderGLWidget::getUniforms()
{
    QList<Uniform> list;

    GLint count = 0;
    GLuint program = shader.programId();
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
    for (int i = 0; i < count; i++)
    {
        Uniform active;
        GLsizei len = 0;
        GLint size = 0;
        GLenum type = 0;
        GLchar name[256] = {0};
        glGetActiveUniform((GLuint)program, (GLuint)i, (GLsizei)255, (GLsizei*)&len, (GLint*)&size, (GLenum*)&type, (GLchar*)&name);
        active.location = glGetUniformLocation(program, name);
        active.name = QString((const char*)name);
        active.type = type;
        list.push_back(active);
    }
    return list;
}

void ShaderGLWidget::setWireframe(bool enable)
{
    wireframe = enable;
}

void ShaderGLWidget::generateCube()
{
    const float vertices[] = {
        -1, -1, -1, // 0 - Front bottom-left
         1, -1, -1, // 1 - Front bottom-right
         1,  1, -1, // 2 - Front upper-right
        -1,  1, -1, // 3 - Front upper-left
        -1,  1,  1, // 4 - Back upper-left
         1,  1,  1, // 5 - Back upper-right
         1, -1,  1, // 6 - Back bottom-right
        -1, -1,  1, // 7 - Back bottom-left
         0,  1,
         1,  1,
         1,  0,
         0,  0,
         0,  1,
         1,  1,
         1,  0,
         0,  0
    };
    const unsigned indices[] = {
        0, 1, 2,   0, 2, 3, // Front
        1, 6, 5,   1, 5, 2, // Right
        6, 7, 4,   6, 4, 5, // Back
        7, 0, 3,   7, 3, 4, // Left
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, (void*)(3*8));
}

void ShaderGLWidget::initializeGL()
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

    proj_location = shader.uniformLocation("projectionMatrix");
    color_location = shader.uniformLocation("colorMult");
    prog = shader.programId();

    glClearColor(1, 1, 0, 1);
    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glViewport(0, 0, width(), height());

    QImage image("../Data/Textures/uv.png");
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    glGenFramebuffers(1, &fbo);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    generateCube();
    glBindVertexArray(0);

    emit contextReady();
}

void ShaderGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void ShaderGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float rotation = 0;
    rotation += 0.5;

    model.setToIdentity();
    model.rotate(rotation, QVector3D(0, 1, 0));

    view.setToIdentity();
    view.lookAt(QVector3D(0, 0,-4),
                QVector3D(0, 0, 0),
                QVector3D(0, 1, 0));

    projection.setToIdentity();
    projection.perspective(60.0, (double)width()/(double)height(), 0.01, 10000.0);

    QMatrix4x4 modelViewProjection = projection * view * model;

    glBindTexture(GL_TEXTURE_2D, tex);
    glUseProgram(prog);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, &modelViewProjection(0, 0));
    glUniform3f(color_location, 1, 1, 1);
    glBindVertexArray(vao);
    if (wireframe)
    {
        glDrawElements(GL_LINES, 36, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
