#include "VertexArray.h"
#include <Engine/Render/API.h>
using namespace Render;

VertexArray::VertexArray()
    : indexArraySize(0)
{
    glGenVertexArrays(1, &handle);
    glGenBuffers(1, &indexArrayID);
}

VertexArray::~VertexArray()
{
    for(auto vbo : buffers) {
        deleteBuffer(vbo.id);
    }
    glDeleteBuffers(1, &indexArrayID);
    glDeleteVertexArrays(1, &handle);
}

int VertexArray::createBufferEx(void* data, size_t sizeElement, size_t numElements, GLenum usageHint)
{
    // Create a new, null buffer
    buffers.push_back({0, 0});
    // Get a reference to it
    auto& newVBO = buffers.back();
    // Generate a buffer on its ID
    glGenBuffers(1, &newVBO.id);
    glBindBuffer(GL_ARRAY_BUFFER, newVBO.id);
    glBufferData(GL_ARRAY_BUFFER, sizeElement * numElements, data, usageHint);
    // Set the buffer size property
    newVBO.count = numElements;
    // And return the buffer's index in the array (last position)
    return buffers.size()-1;
}

int VertexArray::deleteBuffer(int vbo)
{
    if(vbo >= 0 and vbo < (int)buffers.size()) {
        glDeleteBuffers(1, &buffers[vbo].id);
        buffers.erase(buffers.begin() + vbo);
        return vbo;
    } else {
        return -1;
    }
}

int VertexArray::getBufferCount() const
{
    return (int)buffers.size();
}

void VertexArray::setIndexArrayEx(void* data, size_t sizeElement, size_t numElements, GLenum usageHint)
{
    if(data) {
        glBindVertexArray(handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeElement * numElements, data, usageHint);
        indexArraySize = numElements;
    } else {
        indexArraySize = 0;
    }
}

void VertexArray::addAttrib(GLuint index, int vbo, GLuint size, GLenum type, GLvoid* offset, GLint stride)
{
    glBindVertexArray(handle);
    glEnableVertexAttribArray(index);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[vbo].id);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void VertexArray::removeAttrib(GLuint index)
{
    glBindVertexArray(handle);
    glDisableVertexAttribArray(index);
}

void VertexArray::drawElements(GLenum mode)
{
    glBindVertexArray(handle);
    if(indexArraySize) {
        glDrawElements(mode, indexArraySize, GL_UNSIGNED_INT, NULL);
    } else {
        glDrawArrays(mode, 0, buffers[0].count);
    }
}
