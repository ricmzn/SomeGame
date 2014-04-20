#include "BitmapText.h"
#include <Base/Filesystem/File.h>
#include <cstring>

static GLuint newShader(GLenum shaderType, const char* source)
{
    // Tutorial code from http://www.arcsynthesis.org/gltut
    // Copyright © 2012 Jason L. McKesson
    // Variable names changed take custom parameters and work with glLoadGen func_cpp functions
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == false)
    {
       GLint infoLogLength;
       glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

       GLchar *strInfoLog = new GLchar[infoLogLength + 1];
       glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

       const char *strShaderType = NULL;
       switch(shaderType)
       {
       case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
       case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
       case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
       }

       fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
       delete[] strInfoLog;
    }
    return shader;
}

static GLuint initShader()
{
    File vshFile("Shaders/SimpleText.vert");
    File fshFile("Shaders/SimpleText.frag");
    GLuint vsh = newShader(GL_VERTEX_SHADER, vshFile.toString().c_str());
    GLuint fsh = newShader(GL_FRAGMENT_SHADER, fshFile.toString().c_str());

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vsh);
    glAttachShader(prog, fsh);
    glLinkProgram(prog);
    glDetachShader(prog, vsh);
    glDetachShader(prog, fsh);
    return prog;
}

bool BitmapText::isShaderInit = false;
GLuint BitmapText::shaderProgram;

BitmapText::BitmapText(const char* text)
    : text(text)
{
    if (!isShaderInit)
    {
        shaderProgram = initShader();
        isShaderInit = true;
    }
    verts     = nullptr;
    texCoords = nullptr;
    glGenVertexArrays(1, &VAO_id);
}

BitmapText::~BitmapText()
{
    glDeleteVertexArrays(1, &VAO_id);
    glDeleteBuffers(2, VBO_ids);
}

void BitmapText::buildQuads()
{
    const Vec2 charSize = {
        textInfo.char_width,
        textInfo.char_height
    };
    const unsigned faceVerts = 6;
    const unsigned numFaces = strlen(text);

    numVerts  = numFaces*faceVerts;
    verts     = new Vec3[numVerts];
    texCoords = new Vec2[numVerts];

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

    glBindVertexArray(VAO_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(2, VBO_ids);

    // Vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ids[0]);
    glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vec3), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ids[1]);
    glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vec2), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);

    delete[] verts;
    delete[] texCoords;
}

void BitmapText::draw(const Vec2& pos) const
{
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_RECTANGLE, textInfo.texture);
    glBindVertexArray(VAO_id);
    glUseProgram(shaderProgram);

    GLuint offsetLocation = glGetUniformLocation(shaderProgram, "offset");
    glUniform2f(offsetLocation, pos.x, pos.y);
    glDrawArrays(GL_TRIANGLES, 0, numVerts);

    glBindTexture(GL_TEXTURE_RECTANGLE, GL_NONE);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
    glEnable(GL_DEPTH_TEST);
}

#include <SDL2/SDL.h>
void loadBitmapTextSDL(BitmapText *bt, const File &tex)
{
    SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(tex.data(), tex.size()), SDL_FALSE);

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_RECTANGLE, texture_id);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, surf->w, surf->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_RECTANGLE, GL_NONE);

    bt->textInfo.texture_width = surf->w;
    bt->textInfo.texture_height = surf->h;
    bt->textInfo.char_width = 8;
    bt->textInfo.char_height = 12;
    bt->textInfo.texture = texture_id;
    bt->textInfo.columns = 16;
    bt->buildQuads();
}
