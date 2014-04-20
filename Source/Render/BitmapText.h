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
    GLuint texture;
};

class BitmapText
{
    private:
        GLuint VAO_id;
        GLuint VBO_ids[2];
        static bool isShaderInit;
        static GLuint shaderProgram;
        unsigned numVerts;
        Vec3* verts;
        Vec2* texCoords;
        const char* text;
    public:
        BMPTextInfo textInfo;

        BitmapText(const char* text);
        ~BitmapText();
        void buildQuads();
        void draw(const Vec2& pos) const;
};

void loadBitmapTextSDL(BitmapText* bt, const File& tex);

#endif // BITMAPTEXT_H
