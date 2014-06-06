#include "UniverseManager.h"
#include <Engine/System/Application.h>
#include <Engine/Base/Exceptions.h>
#include <Engine/Filesystem/File.h>
#include <SDL2/SDL.h>
using namespace Universe;

UniverseManager::UniverseManager(const PlayerController& player)
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
    matrixLocation = glGetUniformLocation(shader, "matrix");

    SDL_Surface* surf;
    // Load the 1D heatmap texture
    surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(heatFile.data(), heatFile.size()), 1);
    surf = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGB24, 0);
    glGenTextures(1, &heatTexture);
    glBindTexture(GL_TEXTURE_1D, heatTexture);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, surf->w, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(surf);
    // Load the 2D mask texture
    surf = SDL_LoadBMP_RW(SDL_RWFromConstMem(maskFile.data(), maskFile.size()), 1);
    surf = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGB24, 0);
    glGenTextures(1, &maskTexture);
    glBindTexture(GL_TEXTURE_2D, maskTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    SDL_FreeSurface(surf);
}

UniverseManager::~UniverseManager()
{
    for (auto star : stars)
    {
        delete star;
    }
}

void UniverseManager::spawn()
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

void UniverseManager::think()
{}

void UniverseManager::draw(const Camera* camera)
{
    glUseProgram(shader);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_1D, heatTexture);
    glBindTexture(GL_TEXTURE_2D, maskTexture);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &camera->getMatrix()[0][0]);
    glDrawArrays(GL_POINTS, 0, vbo.size());
}

const Array<SpaceObject*>& UniverseManager::getStars() const
{
    return stars;
}
