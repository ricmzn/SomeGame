#ifndef MESHENTITY_H
#define MESHENTITY_H
#include <Engine/Render/Camera.h>
#include <Engine/Base/BinaryMesh.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Render/VertexArray.h>

class MeshEntity : public TransformEntity
{
    private:
        Mat4 modelMatrix;
        Render::VertexArray vertexArray;
        Render::VertexBuffer vertexBuffer;
        Render::VertexBuffer normalBuffer;
        Render::VertexBuffer texCoordBuffer;
        Render::VertexBuffer elementBuffer;
        Render::ShaderProgram unlitShader;
    public:
        GLuint texture;
        float scale;

        MeshEntity();
        void setMesh(const BinaryMesh* mesh);
        void draw(const Render::Camera* camera);
};

#endif // MESHENTITY_H
