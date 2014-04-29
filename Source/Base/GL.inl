#include "GL.h"

template <typename T>
void VertexBufferObject::upload(T* data, size_t len)
{
    glBindBuffer(bufferTarget, handle);
    glBufferData(bufferTarget, len * sizeof(T), data, bufferUsage);
    glBindBuffer(bufferTarget, GL_NONE);
    bufferSize = len;
}
