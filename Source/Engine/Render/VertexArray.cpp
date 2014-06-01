#include "VertexArray.h"
using namespace Render;

VertexArray::VertexArray()
    : indexArray(0)
{
    glGenVertexArrays(1, &handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &handle);
}

void VertexArray::setIndexArray(const VertexBuffer& ibo)
{
    indexArray = ibo.getHandle();
}

void VertexArray::addAttrib(const VertexBuffer& vbo,
                                  GLuint index, GLuint size, GLenum type, GLvoid* offset, GLint stride)
{
    glBindVertexArray(handle);
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArray);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void VertexArray::removeAttrib(GLuint index)
{
    glBindVertexArray(handle);
    glDisableVertexAttribArray(index);
    glBindVertexArray(GL_NONE);
}
