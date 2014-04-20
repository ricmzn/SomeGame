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
#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * @brief Loads OpenGL functions in the current context through GLEW
 * @throws InitializationException if glewInit() fails
 */
void glInitializeContext();

class GLBaseObject
{
    private:
        GLuint handle;
    public:
        GLBaseObject();
        virtual ~GLBaseObject() = 0;
};

class ShaderProgram : GLBaseObject
{

};

class VertexBufferObject : GLBaseObject
{

};

class VertexArrayObject : GLBaseObject
{

};

class Texture2D : GLBaseObject
{

};

#endif // GL_H
