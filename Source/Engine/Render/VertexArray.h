#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include <Engine/Render/ContextObject.h>
#include <Engine/Render/ShaderProgram.h>

namespace Render {
class api_public VertexArray : public ContextObject
{
    private:
        struct VertexBuffer
        {
            GLuint id;
            GLuint count;
        };

        GLuint indexArrayID;
        GLuint indexArraySize;
        Array<VertexBuffer> buffers;
    public:
        VertexArray();
        virtual ~VertexArray();

        /**
         * @brief Creates a new vertex buffer under this VAO object
         * @return Buffer ID
         */
        int createBufferEx(void* data, size_t sizeElement, size_t numElements, GLenum usageHint = GL_STATIC_DRAW);

        /**
         * @brief Deletes a buffer and frees the associated memory
         * @return Buffer ID if successful, -1 otherwise
         */
        int deleteBuffer(int vbo);

        /**
         * @brief getBufferCount
         * @return Number of allocated buffers
         */
        int getBufferCount() const;

        /**
         * @brief Sets the element index array for this VAO
         */
        void setIndexArrayEx(void* data, size_t sizeElement, size_t numElements, GLenum usageHint = GL_STATIC_DRAW);

        /**
         * @brief addAttrib
         * @param index
         * @param vbo
         * @param size
         * @param type
         * @param offset
         * @param stride
         */
        void addAttrib(GLuint index, int vbo, GLuint size, GLenum type, GLvoid* offset = 0, GLint stride = 0);

        /**
         * @brief removeAttrib
         * @param vboID
         */
        void removeAttrib(GLuint index);

        /**
         * @brief drawElements
         * @param shader
         */
        void drawElements(GLenum mode = GL_TRIANGLES);

        template <typename T>
        int createBuffer(T* data, size_t size, GLenum usageHint = GL_STATIC_DRAW)
        {
            return createBufferEx(data, sizeof(data[0]), size, usageHint);
        }

        template <typename T>
        void setIndexArray(T* data, size_t size, GLenum usageHint = GL_STATIC_DRAW)
        {
            setIndexArrayEx(data, sizeof(data[0]), size, usageHint);
        }

};
}

#endif // VERTEXARRAY_H
