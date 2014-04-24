#ifndef TESTTERRAIN_H
#define TESTTERRAIN_H
#include <Base/SharedTypes.h>
#include <Base/GL.h>
#include <vector>

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

        std::vector<Quad> quads;
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
        void generate(float frequency, float amplitude);
        void draw();
};

#endif // TESTTERRAIN_H
