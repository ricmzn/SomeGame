#ifndef GL_H
#define GL_H
#ifdef __GNUC__
  #ifndef __COUNTER__
// Works around Qt Creator's macro auto-completion
// __GNUC__ is defined during its parsing, but __COUNTER__ is not
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
  #endif
#endif
#include <GL/glew.h>
#include <string>

/**
 * @brief Loads OpenGL functions in the current context through GLEW
 * @throws InitializationException if glewInit() fails
 */
void glInitializeContext();

class GLBaseObject
{
    protected:
        GLuint handle;
    public:
        GLBaseObject();
        virtual ~GLBaseObject() = 0;
        GLuint getHandle() const;
        operator GLuint() const;
};

class ShaderProgram : public GLBaseObject
{
    protected:
        std::string errorLog;
    public:
        ShaderProgram();
        virtual ~ShaderProgram();
        void addShader(GLenum type, const GLchar* src, GLint size);
        const char* getLog() const;
        void link();
};

class VertexBufferObject : public GLBaseObject
{
    protected:
        GLenum bufferTarget;
        GLenum bufferUsage;
        GLuint bufferSize;
    public:
        VertexBufferObject(GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
        virtual ~VertexBufferObject();
        void uploadTypeSize(void* data, size_t size, size_t len);
        GLuint target() const;
        GLuint size() const;

        /**
         * @brief Same as uploadTypeSize, but with compile-time size deduction
         */
        template <typename T> void upload(T* data, size_t len)
        {
            this->uploadTypeSize(data, sizeof(T), len);
        }
};

class VertexArrayObject : public GLBaseObject
{
    protected:
        GLuint indexArray;
    public:
        VertexArrayObject();
        virtual ~VertexArrayObject();
        void setIndexArray(const VertexBufferObject& ibo);
        void addAttrib(const VertexBufferObject& vbo,
                       GLuint index, GLuint size, GLenum type, GLvoid* offset = 0, GLint stride = 0);
        void removeAttrib(GLuint index);
};

class Texture2D : public GLBaseObject
{
    protected:
        GLsizei texWidth, texHeight;
    public:
        Texture2D();
        virtual ~Texture2D();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height, GLint level = 0);
        GLsizei width() const;
        GLsizei height() const;
};

class Texture2DRect : public Texture2D
{
    public:
        Texture2DRect();
        virtual ~Texture2DRect();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height);
};

#endif // GL_H
