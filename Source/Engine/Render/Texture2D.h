#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <Engine/Render/ContextObject.h>

namespace Render {
class api_public Texture2D : public ContextObject
{
    public:
        Texture2D();
        virtual ~Texture2D();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height, GLint level = 0, GLenum internal = GL_RGBA);
};
}

#endif // TEXTURE2D_H
