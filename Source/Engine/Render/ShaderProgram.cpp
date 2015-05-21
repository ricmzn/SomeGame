#include "ShaderProgram.h"
#include <Engine/Render/API.h>
using namespace Render;

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
