#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <Engine/Render/ContextObject.h>
#include <Engine/Render/VertexBuffer.h>

namespace Render
{
    class VertexArray : public ContextObject
    {
    protected:
        GLuint indexArray;

    public:
        VertexArray();
        virtual ~VertexArray();
        void setIndexArray(const VertexBuffer& ibo);
        void addAttrib(const VertexBuffer& vbo, GLuint index, GLuint size, GLenum type, GLvoid* offset = 0, GLint stride = 0);
        void removeAttrib(GLuint index);
    };
}

#endif // VERTEXARRAY_H
