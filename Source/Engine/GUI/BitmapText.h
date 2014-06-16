#ifndef BITMAPTEXT_H
#define BITMAPTEXT_H
#include <Engine/Filesystem/File.h>
#include <Engine/Base/SharedTypes.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Render/TextureRect.h>
#include <Engine/Render/VertexArray.h>

struct BMPTextInfo
{
    short texture_width;
    short texture_height;
    short char_width;
    short char_height;
    short columns;
    Render::TextureRect texture;
};

class BitmapText
{
    private:
        Render::ShaderProgram shaderProgram;
        Render::VertexArray vertexArray;
        Render::VertexBuffer vertexBuffer;
        Render::VertexBuffer texCoordBuffer;
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
