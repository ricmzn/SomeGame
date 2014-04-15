#ifndef WORLDMODEL_H
#define WORLDMODEL_H
#include <Base/BinaryMesh.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

class WorldModel
{
    private:
        glm::mat4 modelMatrix;
        GLuint vertexArray;
        GLuint vertexBuffer;
        GLuint texCoordBuffer;
        GLuint normalBuffer;
        GLuint elementBuffer;

        void uploadGeometry(const BinaryMesh& mesh) const
        {
            glBindVertexArray(vertexArray);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, mesh.header.nVerts * sizeof(Vec3), mesh.verts, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
            glBufferData(GL_ARRAY_BUFFER, mesh.header.nVerts * sizeof(Vec2), mesh.texCoords, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
            glBufferData(GL_ARRAY_BUFFER, mesh.header.nVerts * sizeof(Vec3), mesh.normals, GL_STATIC_DRAW);
            glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.header.nIndices * sizeof(uint32_t), mesh.indices, GL_STATIC_DRAW);

            glBindVertexArray(0);
        }

    public:
        WorldModel(const BinaryMesh& mesh)
        {
            glGenVertexArrays(1, &vertexArray);
            glGenBuffers(1, &vertexBuffer);
            glGenBuffers(1, &texCoordBuffer);
            glGenBuffers(1, &normalBuffer);
            glGenBuffers(1, &elementBuffer);

            this->uploadGeometry(mesh);
        }
};

#endif // WORLDMODEL_H
