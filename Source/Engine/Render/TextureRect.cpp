#include "TextureRect.h"
using namespace Render;

TextureRect::TextureRect()
{
    glGenTextures(1, &handle);
}

TextureRect::~TextureRect()
{
    glDeleteTextures(1, &handle);
}

void TextureRect::upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height, GLenum internal)
{
    glBindTexture(GL_TEXTURE_RECTANGLE, handle);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, internal, width, height, 0, format, type, pixels);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
