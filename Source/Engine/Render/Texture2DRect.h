#ifndef TEXTURE2DRECT_H
#define TEXTURE2DRECT_H
#include <Engine/Render/ContextObject.h>
#include <Engine/Render/Texture2D.h>

namespace Render
{
    class Texture2DRect : public Texture2D
    {
    public:
        Texture2DRect();
        virtual ~Texture2DRect();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height);
    };
}


#endif // TEXTURE2DRECT_H
