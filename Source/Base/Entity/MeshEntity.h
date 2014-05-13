#ifndef MESHENTITY_H
#define MESHENTITY_H
#include <Entities/Camera.h>
#include <Base/BinaryMesh.h>
#include <Base/GL.h>

class MeshEntity : public TransformEntity
{
    private:
        Mat4 modelMatrix;
        VertexArrayObject vertexArray;
        VertexBufferObject vertexBuffer;
        VertexBufferObject normalBuffer;
        VertexBufferObject texCoordBuffer;
        VertexBufferObject elementBuffer;
    public:
        GLuint texture;
        float scale;

        MeshEntity();
        void setMesh(const BinaryMesh* mesh);
        void draw(const Camera* camera);
};

#endif // MESHENTITY_H
