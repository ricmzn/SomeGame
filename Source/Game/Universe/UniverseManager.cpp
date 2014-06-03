#include "UniverseManager.h"
#include <Engine/System/Application.h>
#include <Engine/Base/Exceptions.h>
#include <Engine/Filesystem/File.h>
using namespace Universe;

UniverseManager::UniverseManager(const PlayerController& player)
    : reference(player.transform.pos)
{
    File vshFile("Shaders/PointStar.vert");
    File fshFile("Shaders/PointStar.frag");
    shader.addShader(GL_VERTEX_SHADER, vshFile.toString().c_str(), vshFile.size());
    shader.addShader(GL_FRAGMENT_SHADER, fshFile.toString().c_str(), fshFile.size());
    shader.link();
    if (shader.getLog())
    {
        throw GenericError(shader.getLog());
    }
    matrixLocation = glGetUniformLocation(shader, "matrix");
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
    const int maxStars = 8192;
    const float maxRange = 32768;
    vbo.uploadTypeSize(NULL, sizeof(Vec4), maxStars);
    for (int i = 0; i < maxStars; i++)
    {
        Vec4 pos;
        pos.x = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.y = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.z = (float(rand())/RAND_MAX) * maxRange - maxRange/2;
        pos.w =  float(rand())/RAND_MAX;

        const GLintptr offset = i * sizeof(Vec4);
        vbo.uploadOffset(&pos, sizeof(Vec4), 1, offset);
//        stars.push_back(new SpaceObject(Vec3(pos.x, pos.y, pos.z)));
    }
    vao.addAttrib(vbo, 0, 4, GL_FLOAT);
}

void UniverseManager::think()
{}

void UniverseManager::draw(const Camera* camera)
{
    glBindVertexArray(vao);
    glUseProgram(shader);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &camera->getMatrix()[0][0]);
    glDrawArrays(GL_POINTS, 0, vbo.size());
}

const Array<SpaceObject*>& UniverseManager::getStars() const
{
    return stars;
}
