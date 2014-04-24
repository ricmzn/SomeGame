#include "GL.h"
#include <Base/Exceptions.h>

/*-----------------*/
/* Loose functions */
/*-----------------*/
void glInitializeContext()
{
    // Required for Core contexts
    glewExperimental = GL_TRUE;
    // Try initializing GLEW
    if (glewInit() == GLEW_OK);
    // If it doesn't work, blame the user
    else throw InitializationException(
                "Failed to initialize OpenGL context\n"
                "Try updating your video driver to its latest version");
}

/*--------------*/
/* GLBaseObject */
/*--------------*/
GLBaseObject::GLBaseObject()
    : handle(GL_NONE)
{}

GLBaseObject::~GLBaseObject()
{}

GLuint GLBaseObject::getHandle() const
{
    return handle;
}

GLBaseObject::operator GLuint() const
{
    return handle;
}

/*---------------*/
/* ShaderProgram */
/*---------------*/
ShaderProgram::ShaderProgram()
    : errorLog()
{
    handle = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(handle);
}

void ShaderProgram::addShader(GLenum type, const GLchar* src, GLint size)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, &size);
    glCompileShader(shader);

    GLint shaderCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

    if (shaderCompiled)
    {
        glAttachShader(handle, shader);
    }
    else
    {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        GLchar* logBuffer = new char[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, logBuffer);

        errorLog.append(logBuffer);
        delete[] logBuffer;
    }

    glDeleteShader(shader);
}

const char* ShaderProgram::getLog() const
{
    if (errorLog.size() > 0)
    {
        return errorLog.c_str();
    }
    else
    {
        return nullptr;
    }
}

void ShaderProgram::link()
{
    glLinkProgram(handle);

    GLint programLinked = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &programLinked);

    if (programLinked)
    {
        // Everything is fine, captain!
    }
    else
    {
        GLint logLength = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);

        GLchar* logBuffer = new char[logLength];
        glGetProgramInfoLog(handle, logLength, NULL, logBuffer);

        errorLog.append(logBuffer);
        delete[] logBuffer;
    }
}

/*--------------------*/
/* VertexBufferObject */
/*--------------------*/
VertexBufferObject::VertexBufferObject(GLenum target, GLenum usage)
    : bufferTarget(target), bufferUsage(usage), bufferSize(0)
{
    glGenBuffers(1, &handle);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &handle);
}

void VertexBufferObject::upload(void* data, size_t len)
{
    glBindBuffer(bufferTarget, handle);
    glBufferData(bufferTarget, len, data, bufferUsage);
    glBindBuffer(bufferTarget, GL_NONE);
    bufferSize = len;
}

GLuint VertexBufferObject::target() const
{
    return bufferTarget;
}

GLuint VertexBufferObject::size() const
{
    return bufferSize;
}

/*-------------------*/
/* VertexArrayObject */
/*-------------------*/
VertexArrayObject::VertexArrayObject()
    : indexArray(0)
{
    glGenVertexArrays(1, &handle);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &handle);
}

void VertexArrayObject::setIndexArray(const VertexBufferObject& ibo)
{
    indexArray = ibo.getHandle();
}

void VertexArrayObject::addAttrib(const VertexBufferObject& vbo,
                                  GLuint index, GLuint size, GLenum type, GLint offset, GLint stride)
{
    glBindVertexArray(handle);
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
}

void VertexArrayObject::removeAttrib(GLuint index)
{
    glBindVertexArray(handle);
    glDisableVertexAttribArray(index);
    glBindVertexArray(GL_NONE);
}

/*-----------*/
/* Texture2D */
/*-----------*/
Texture2D::Texture2D()
    : texWidth(0), texHeight(0)
{
    glGenTextures(1, &handle);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &handle);
}

void Texture2D::upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height, GLint level)
{
    glBindTexture(GL_TEXTURE_2D, handle);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

GLsizei Texture2D::width() const
{
    return texWidth;
}

GLsizei Texture2D::height() const
{
    return texHeight;
}

/*---------------*/
/* Texture2DRect */
/*---------------*/
Texture2DRect::Texture2DRect()
{
    glGenTextures(1, &handle);
}

Texture2DRect::~Texture2DRect()
{
    glDeleteTextures(1, &handle);
}

void Texture2DRect::upload(void* pixels, GLenum format, GLenum typ, GLsizei width, GLsizei height)
{
    glBindTexture(GL_TEXTURE_RECTANGLE, handle);
    glBindTexture(GL_TEXTURE_RECTANGLE, GL_NONE);
}
