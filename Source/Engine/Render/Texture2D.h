#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#include <Engine/Render/ContextObject.h>

namespace Render
{
    class Texture2D : public ContextObject
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
}

#endif // TEXTURE2D_H
