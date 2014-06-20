#ifndef MESHENTITY_H
#define MESHENTITY_H
#include <Engine/Entity/DrawableEntity.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Render/VertexArray.h>
#include <Engine/Base/BinaryMesh.h>

class MeshEntity : public DrawableEntity
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

        MeshEntity(const String& name = "");
        void setMesh(const BinaryMesh* mesh);
        virtual void draw(const Camera* camera);
};

#endif // MESHENTITY_H
