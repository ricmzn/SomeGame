#include "BitmapText.h"
#include <Engine/Filesystem/File.h>
#include <cstring>

BitmapText::BitmapText()
    : vertexBuffer(GL_ARRAY_BUFFER),
      texCoordBuffer(GL_ARRAY_BUFFER),
      text(nullptr)
{
    File shaderFile;
    shaderFile.setFile("Shaders/SimpleText.vert");
    shaderProgram.addShader(GL_VERTEX_SHADER, shaderFile.toString().c_str(), shaderFile.size());
    shaderFile.setFile("Shaders/SimpleText.frag");
    shaderProgram.addShader(GL_FRAGMENT_SHADER, shaderFile.toString().c_str(), shaderFile.size());
    shaderProgram.link();
}

BitmapText::~BitmapText()
{}

void BitmapText::setString(const char *text)
{
    this->text = text;
    this->buildQuads();
}

void BitmapText::buildQuads()
{
    if (!text) return;

    const Vec2 charSize = {
        textInfo.char_width,
        textInfo.char_height
    };
    const unsigned faceVerts = 6;
    const unsigned numFaces = strlen(text);

    GLuint  numVerts  = numFaces*faceVerts;
    Vec3*   verts     = new Vec3[numVerts];
    Vec2*   texCoords = new Vec2[numVerts];

    for (unsigned i = 0; i < numFaces; i++)
    {
        // Vertex positions
        const Vec3 topLeft  = {charSize.x * (i+0), charSize.y, 0};
        const Vec3 topRight = {charSize.x * (i+1), charSize.y, 0};
        const Vec3 botLeft  = {charSize.x * (i+0), 0,          0};
        const Vec3 botRight = {charSize.x * (i+1), 0,          0};

        verts[i*faceVerts+0] = topLeft;
        verts[i*faceVerts+1] = botLeft;
        verts[i*faceVerts+2] = botRight;
        verts[i*faceVerts+3] = topRight;
        verts[i*faceVerts+4] = topLeft;
        verts[i*faceVerts+5] = botRight;

        // And texture coordinates
        const Vec2 charOffset = {
            text[i] % textInfo.columns * charSize.x,
            text[i] / textInfo.columns * charSize.y
        };

        texCoords[i*faceVerts+0] = {charOffset.x,              charOffset.y};
        texCoords[i*faceVerts+1] = {charOffset.x,              charOffset.y + charSize.y};
        texCoords[i*faceVerts+2] = {charOffset.x + charSize.x, charOffset.y + charSize.y};
        texCoords[i*faceVerts+3] = {charOffset.x + charSize.x, charOffset.y};
        texCoords[i*faceVerts+4] = {charOffset.x,              charOffset.y};
        texCoords[i*faceVerts+5] = {charOffset.x + charSize.x, charOffset.y + charSize.y};
    }

    vertexBuffer.upload(verts, numVerts);
    texCoordBuffer.upload(texCoords, numVerts);
    vertexArray.addAttrib(vertexBuffer, 0, 3, GL_FLOAT);
    vertexArray.addAttrib(texCoordBuffer, 1, 2, GL_FLOAT);

    delete[] verts;
    delete[] texCoords;
}

void BitmapText::draw(float x, float y) const
{
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_RECTANGLE, textInfo.texture);
    glBindVertexArray(vertexArray);
    glUseProgram(shaderProgram);

    GLuint offsetLocation = glGetUniformLocation(shaderProgram, "offset");
    glUniform2f(offsetLocation, x, y);

    glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size());

    glBindTexture(GL_TEXTURE_RECTANGLE, GL_NONE);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
    glEnable(GL_DEPTH_TEST);
}

#include <SDL2/SDL.h>
void loadBitmapTextSDL(const char* str, const File &tex, BitmapText* bt)
{
    SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(tex.data(), tex.size()), 1);

    bt->textInfo.texture_width = surf->w;
    bt->textInfo.texture_height = surf->h;
    bt->textInfo.char_width = 8;
    bt->textInfo.char_height = 12;
    bt->textInfo.texture.upload(surf->pixels, GL_BGR, GL_UNSIGNED_BYTE, surf->w, surf->h);
    bt->textInfo.columns = 16;
    bt->setString(str);

    SDL_FreeSurface(surf);
}
