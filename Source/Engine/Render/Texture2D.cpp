#include "Texture2D.h"
using namespace Render;

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
