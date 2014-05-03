#include "TestTerrain.h"
#include <Base/Filesystem/File.h>
#include <Base/NumberGenerator.h>
#include <Base/SharedTypes.h>
#include <glm/gtc/matrix_transform.hpp>

void TestTerrain::subdivide(int levels)
{
    while (levels --> 0)
    {
        for (size_t i = quads.size(); i > 0; i--)
        {
            TestTerrain::Quad original = quads[i-1];
            quads.erase(quads.begin() + i - 1);

            const Vec3 originalCenter   = (original.northWest + original.southWest +  original.southEast + original.northEast) / 4.f;
            const Vec3 originalWest     = (original.northWest + original.southWest) / 2.f;
            const Vec3 originalSouth    = (original.southWest + original.southEast) / 2.f;
            const Vec3 originalEast     = (original.southEast + original.northEast) / 2.f;
            const Vec3 originalNorth    = (original.northEast + original.northWest) / 2.f;

            const Quad NW = {
                original.northWest,
                originalWest,
                originalCenter,
                originalNorth
            };
            const Quad SW = {
                originalWest,
                original.southWest,
                originalSouth,
                originalCenter
            };
            const Quad SE = {
                originalCenter,
                originalSouth,
                original.southEast,
                originalEast
            };
            const Quad NE = {
                originalNorth,
                originalCenter,
                originalEast,
                original.northEast
            };

            quads.push_back(NW);
            quads.push_back(SW);
            quads.push_back(SE);
            quads.push_back(NE);
        }
    }
}

void TestTerrain::triangulate()
{
    const unsigned nVertices = quads.size() * 5;
    const unsigned nIndices = quads.size() * 12;
    Vec3* vertices = new Vec3[nVertices];
    GLuint* indices = new GLuint[nIndices];

    for (size_t i = 0; i < quads.size(); i++)
    {
        const Quad& quad = quads[i];
        const Vec3 center = (quad.northWest + quad.southWest +  quad.southEast + quad.northEast) / 4.f;
        vertices[i*5 + 0] = quad.northWest;
        vertices[i*5 + 1] = quad.southWest;
        vertices[i*5 + 2] = quad.southEast;
        vertices[i*5 + 3] = quad.northEast;
        vertices[i*5 + 4] = center;

        // Left triangle
        indices[i*12 + 0] = i*5 + 0;
        indices[i*12 + 1] = i*5 + 1;
        indices[i*12 + 2] = i*5 + 4;
        // Bottom triangle
        indices[i*12 + 3] = i*5 + 1;
        indices[i*12 + 4] = i*5 + 2;
        indices[i*12 + 5] = i*5 + 4;
        // Right triangle
        indices[i*12 + 6] = i*5 + 2;
        indices[i*12 + 7] = i*5 + 3;
        indices[i*12 + 8] = i*5 + 4;
        // Upper triangle
        indices[i*12 + 9] = i*5 + 3;
        indices[i*12 +10] = i*5 + 0;
        indices[i*12 +11] = i*5 + 4;
    }
    vbo.upload(vertices, nVertices);
    ibo.upload(indices, nIndices);
    vao.setIndexArray(ibo);
    vao.addAttrib(vbo, 0, 3, GL_FLOAT);
    delete[] vertices;
    delete[] indices;
}

TestTerrain::TestTerrain(int width, int height, int lod)
    : vbo(GL_ARRAY_BUFFER),
      ibo(GL_ELEMENT_ARRAY_BUFFER),
      pitch(width)
{
    File shaderFile;
    shaderFile.setFile("Shaders/TerrainHeight.vert");
    shader.addShader(GL_VERTEX_SHADER, shaderFile.toString().c_str(), shaderFile.size());
    shaderFile.setFile("Shaders/TerrainHeight.frag");
    shader.addShader(GL_FRAGMENT_SHADER, shaderFile.toString().c_str(), shaderFile.size());
    shader.link();

    if (shader.getLog())
    {
        //fprintf(stderr, "%s", shader.getLog());
        throw InitializationException(shader.getLog());
    }

    Quad start;
    start.northWest = {0,     0, 0};
    start.southWest = {0,     0, height};
    start.southEast = {width, 0, height};
    start.northEast = {width, 0, 0};
    quads.push_back(start);
    this->subdivide(lod);
}

TestTerrain::~TestTerrain()
{

}

void TestTerrain::generate(float frequency, float amplitude, int seed,
                           float exponent, int octaves, float x, float y)
{
    NumberGenerator::PerlinNoise2D perlin(seed);
    amplitude /= octaves;
    exponent *= 2;
    while (octaves > 0)
    {
        for (size_t i = 0; i < quads.size(); i++)
        {
            Quad& quad = quads[i];
            quad.northWest.y += perlin.get((quad.northWest.x + x) * frequency, (quad.northWest.z + y) * frequency) * amplitude;
            quad.southWest.y += perlin.get((quad.southWest.x + x) * frequency, (quad.southWest.z + y) * frequency) * amplitude;
            quad.southEast.y += perlin.get((quad.southEast.x + x) * frequency, (quad.southEast.z + y) * frequency) * amplitude;
            quad.northEast.y += perlin.get((quad.northEast.x + x) * frequency, (quad.northEast.z + y) * frequency) * amplitude;
        }
        amplitude *= exponent;
        frequency /= exponent;
        octaves--;
    }
    this->triangulate();
}

void TestTerrain::draw(float x, float y, float z, const Camera* camera)
{
    glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, y, z));
    glm::mat4 MVP = camera->getMatrix() * model;

    glUseProgram(shader);
    GLuint projLocation = glGetUniformLocation(shader, "projectionMatrix");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, ibo.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
}
