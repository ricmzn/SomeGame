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

    if (!shaderCompiled)
    {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        GLchar* logBuffer = new char[logLength];
        glGetShaderInfoLog(shader, logLength, NULL, logBuffer);

        errorLog.append(logBuffer);
        delete[] logBuffer;
    }

    glAttachShader(handle, shader);
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

    if (!programLinked)
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

void VertexBufferObject::uploadTypeSize(void* data, size_t size, size_t len)
{
    glBindBuffer(bufferTarget, handle);
    glBufferData(bufferTarget, size * len, data, bufferUsage);
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
                                  GLuint index, GLuint size, GLenum type, GLvoid* offset, GLint stride)
{
    glBindVertexArray(handle);
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
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
    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, format, type, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
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

void Texture2DRect::upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height)
{
    glBindTexture(GL_TEXTURE_RECTANGLE, handle);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, width, height, 0, format, type, pixels);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
