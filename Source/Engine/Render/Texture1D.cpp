#include "Texture1D.h"
using namespace Render;

Texture1D::Texture1D()
{
    glGenTextures(1, &handle);
}

Texture1D::~Texture1D()
{
    glDeleteTextures(1, &handle);
}

void Texture1D::upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLint level, GLenum internal)
{
    glBindTexture(GL_TEXTURE_1D, handle);
    glTexImage1D(GL_TEXTURE_1D, level, internal, width, 0, format, type, pixels);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
