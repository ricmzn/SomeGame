#ifndef WORLDMODEL_H
#define WORLDMODEL_H
#include <Base/BinaryMesh.h>
#include <Base/GL.h>

class WorldModel
{
    private:
        Mat4 modelMatrix;
        VertexArrayObject vertexArray;
        VertexBufferObject vertexBuffer;
        VertexBufferObject normalBuffer;
        VertexBufferObject texCoordBuffer;
        VertexBufferObject elementBuffer;
        void uploadGeometry(const BinaryMesh& mesh);
    public:
        WorldModel(const BinaryMesh& mesh);
};

#endif // WORLDMODEL_H
