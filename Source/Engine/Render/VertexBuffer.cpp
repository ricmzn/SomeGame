#include "VertexBuffer.h"
using namespace Render;

VertexBuffer::VertexBuffer(GLenum target, GLenum usage)
    : bufferTarget(target), bufferUsage(usage), bufferSize(0)
{
    glGenBuffers(1, &handle);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &handle);
}

void VertexBuffer::uploadTypeSize(void* data, size_t size, size_t len)
{
    glBindBuffer(bufferTarget, handle);
    glBufferData(bufferTarget, size * len, data, bufferUsage);
    bufferSize = len;
}

void VertexBuffer::uploadOffset(void* data, size_t size, size_t len, GLintptr offset)
{
    glBindBuffer(bufferTarget, handle);
    glBufferSubData(bufferTarget, offset, size * len, data);
}

GLuint VertexBuffer::target() const
{
    return bufferTarget;
}

GLuint VertexBuffer::size() const
{
    return bufferSize;
}