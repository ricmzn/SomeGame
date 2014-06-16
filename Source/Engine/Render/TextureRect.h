#ifndef TEXTURERECT_H
#define TEXTURERECT_H
#include <Engine/Render/ContextObject.h>

namespace Render
{
    class TextureRect : public ContextObject
    {
    public:
        TextureRect();
        virtual ~TextureRect();
        void upload(void* pixels, GLenum format, GLenum type, GLsizei width, GLsizei height, GLenum internal = GL_RGBA);
    };
}


#endif // TEXTURERECT_H
