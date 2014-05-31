#ifndef BITMAPTEXT_H
#define BITMAPTEXT_H
#include <Engine/Filesystem/File.h>
#include <Engine/Base/SharedTypes.h>
#include <Engine/OpenGL/GL.h>

struct BMPTextInfo
{
    short texture_width;
    short texture_height;
    short char_width;
    short char_height;
    short columns;
    Texture2DRect texture;
};

class BitmapText
{
    private:
        ShaderProgram shaderProgram;
        VertexArrayObject vertexArray;
        VertexBufferObject vertexBuffer;
        VertexBufferObject texCoordBuffer;
        const char* text;
        void buildQuads();
    public:
        BMPTextInfo textInfo;
        BitmapText();
        ~BitmapText();
        void setString(const char* text);
        void draw(float x, float y) const;
};

void loadBitmapTextSDL(const char*, const File& tex, BitmapText* bt);

#endif // BITMAPTEXT_H
