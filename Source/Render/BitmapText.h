#ifndef BITMAPTEXT_H
#define BITMAPTEXT_H
#include <Base/Filesystem/File.h>
#include <Base/SharedTypes.h>
#include <Base/GL.h>

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

BitmapText loadBitmapTextSDL(const char*, const File& tex);

#endif // BITMAPTEXT_H
