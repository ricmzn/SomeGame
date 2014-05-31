#ifndef MESHENTITY_H
#define MESHENTITY_H
#include <Engine/Entity/Camera.h>
#include <Engine/Base/BinaryMesh.h>
#include <Engine/OpenGL/GL.h>

class MeshEntity : public TransformEntity
{
    private:
        Mat4 modelMatrix;
        VertexArrayObject vertexArray;
        VertexBufferObject vertexBuffer;
        VertexBufferObject normalBuffer;
        VertexBufferObject texCoordBuffer;
        VertexBufferObject elementBuffer;
        ShaderProgram unlitShader;
    public:
        GLuint texture;
        float scale;

        MeshEntity();
        void setMesh(const BinaryMesh* mesh);
        void draw(const Camera* camera);
};

#endif // MESHENTITY_H
