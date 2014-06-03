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
        void uploadOffset(void* data, size_t size, size_t len, GLintptr offset);
        GLuint target() const;
        GLuint size() const;

        template <typename T> void upload(T* data, size_t len)
        {
            this->uploadTypeSize(data, sizeof(T), len);
        }

        template <typename T> void upload(T* data, size_t len, GLintptr offset)
        {
            this->uploadOffset(data, sizeof(T), len, offset);
        }
    };
}

#endif // VERTEXBUFFER_H
