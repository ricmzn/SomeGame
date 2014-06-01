#include "Texture2DRect.h"
using namespace Render;

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
