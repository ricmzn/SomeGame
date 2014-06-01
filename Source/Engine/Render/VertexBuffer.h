#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include <Engine/Render/ContextObject.h>

namespace Render
{
    class VertexBuffer : public ContextObject
    {
    protected:
        GLenum bufferTarget;
        GLenum bufferUsage;
        GLuint bufferSize;

    public:
        VertexBuffer(GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
        virtual ~VertexBuffer();
        void uploadTypeSize(void* data, size_t size, size_t len);
        GLuint target() const;
        GLuint size() const;

        // Same as uploadTypeSize, but with an implicit call to sizeof()
        template <typename T> void upload(T* data, size_t len)
        {
            this->uploadTypeSize(data, sizeof(T), len);
        }
    };
}

#endif // VERTEXBUFFER_H
