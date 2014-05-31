#ifndef TESTTERRAIN_H
#define TESTTERRAIN_H
#include <Engine/OpenGL/GL.h>
#include <Engine/Entity/Camera.h>

class TestTerrain
{
    private:
        struct Quad
        {
            Vec3 northWest;
            Vec3 southWest;
            Vec3 southEast;
            Vec3 northEast;
        };

        Array<Quad> quads;
        ShaderProgram shader;
        VertexArrayObject vao;
        VertexBufferObject vbo;
        VertexBufferObject ibo;
        int pitch;

        void subdivide(int levels);
        void triangulate();

    public:
        TestTerrain(int width, int height, int lod);
        ~TestTerrain();
        void generate(float frequency, float amplitude, int seed,
                      float exponent = 1, int octaves = 1, float x = 0, float y = 0);
        void draw(float x, float y, float z, const Camera* camera);
};

#endif // TESTTERRAIN_H
