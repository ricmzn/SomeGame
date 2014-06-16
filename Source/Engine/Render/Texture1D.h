#ifndef TEXTURE1D_H
#define TEXTURE1D_H
#include <Engine/Render/ContextObject.h>

namespace Render
{
    class Texture1D : public ContextObject
    {
    public:
        Texture1D();
        virtual ~Texture1D();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLint level = 0, GLenum internal = GL_RGBA);
    };
}

#endif // TEXTURE1D_H
