#include "Manager.h"
#include <Engine/System/Application.h>
#include <Engine/Base/Exceptions.h>
#include <Engine/Filesystem/File.h>
#include <SDL2/SDL.h>
using namespace Universe;

Manager::Manager(const PlayerController& player)
    : reference(player.transform.pos)
{
    File vshFile("Shaders/PointStar.vert");
    File fshFile("Shaders/PointStar.frag");
    File heatFile("Textures/star_temps.bmp");
    File maskFile("Textures/star_mask.bmp");
    shader.addShader(GL_VERTEX_SHADER, vshFile.toString().c_str(), vshFile.size());
    shader.addShader(GL_FRAGMENT_SHADER, fshFile.toString().c_str(), fshFile.size());
    shader.link();
    if (shader.getLog())
    {
        throw GenericError(shader.getLog());
    }
    glUseProgram(shader);
    matrixLocation = glGetUniformLocation(shader, "matrix");
    heatLocation = glGetUniformLocation(shader, "heatTexture");
    maskLocation = glGetUniformLocation(shader, "maskTexture");
    if (matrixLocation < 0 || heatLocation < 0 || maskLocation < 0)
    {
        throw GenericError("GLSL uniform location binding failed for UniverseManager");
    }
    glUniform1i(heatLocation, 0);
    glUniform1i(maskLocation, 1);

    SDL_Surface* originalSurface;
    SDL_Surface* rgbSurface;

    // Load the 1D heatmap texture
    originalSurface = SDL_LoadBMP_RW(SDL_RWFromConstMem(heatFile.data(), heatFile.size()), 1);
    rgbSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(originalSurface);
    heatTexture.upload(rgbSurface->pixels, GL_RGB, GL_UNSIGNED_BYTE, rgbSurface->w, 0, GL_RGB);
    SDL_FreeSurface(rgbSurface);

    // Load the 2D mask texture
    originalSurface = SDL_LoadBMP_RW(SDL_RWFromConstMem(maskFile.data(), maskFile.size()), 1);
    rgbSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(originalSurface);
    maskTexture.upload(rgbSurface->pixels, GL_RGB, GL_UNSIGNED_BYTE, rgbSurface->w, rgbSurface->h, 0, GL_R8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Enable clamp to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // to avoid artifacts
    SDL_FreeSurface(rgbSurface);
}

Manager::~Manager()
{
    for (auto star : stars)
    {
        delete star;
    }
}

void Manager::spawn()
{
    // Temporary heap memory cost:
    // 32768 * 4 * sizeof(Vec4) = 2MiB
    const int maxStars = 32768*4;
    const float maxRange = 256*256;
    Vec4* stars = new Vec4[maxStars];
    for (int i = 0; i < maxStars; i++)
    {
        Vec4 pos;
        pos.x = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.y = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.z = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.w =  float(rand())/RAND_MAX;
        stars[i] = pos;
    }
    vbo.upload(stars, maxStars);
    vao.addAttrib(vbo, 0, 4, GL_FLOAT);
    delete[] stars;
}

void Manager::think()
{}

void Manager::draw(const Camera* camera)
{
    glUseProgram(shader);
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, heatTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, maskTexture);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &camera->getMatrix()[0][0]);
    glDrawArrays(GL_POINTS, 0, vbo.size());
    glActiveTexture(GL_TEXTURE0);
}

const Array<SpaceObject*>& Manager::getStars() const
{
    return stars;
}
