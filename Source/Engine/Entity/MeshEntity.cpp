#include "MeshEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Filesystem/File.h>
#include <Engine/Base/Exceptions.h>

MeshEntity::MeshEntity()
    : vertexBuffer(GL_ARRAY_BUFFER),
      normalBuffer(GL_ARRAY_BUFFER),
      texCoordBuffer(GL_ARRAY_BUFFER),
      elementBuffer(GL_ELEMENT_ARRAY_BUFFER),
      texture(0),
      scale(1.f)
{
    File vshFile("Shaders/UnlitGeneric.vert");
    File fshFile("Shaders/UnlitGeneric.frag");
    unlitShader.addShader(GL_VERTEX_SHADER, vshFile.toString().c_str(), vshFile.size());
    unlitShader.addShader(GL_FRAGMENT_SHADER, fshFile.toString().c_str(), fshFile.size());
    unlitShader.link();
    if (unlitShader.getLog())
    {
        throw GenericError(unlitShader.getLog());
    }
}

void MeshEntity::setMesh(const BinaryMesh* mesh)
{
    vertexBuffer.upload(mesh->verts, mesh->header.nVerts);
    normalBuffer.upload(mesh->normals, mesh->header.nVerts);
    texCoordBuffer.upload(mesh->texCoords, mesh->header.nVerts);
    elementBuffer.upload(mesh->indices, mesh->header.nIndices);

    vertexArray.setIndexArray(elementBuffer);
    vertexArray.addAttrib(vertexBuffer, 0, 3, GL_FLOAT);
    vertexArray.addAttrib(normalBuffer, 1, 3, GL_FLOAT);
    vertexArray.addAttrib(texCoordBuffer, 2, 2, GL_FLOAT);
}

void MeshEntity::draw(const Camera* camera)
{
    modelMatrix = glm::mat4(1.f);
    modelMatrix = glm::scale(modelMatrix, Vec3(scale, scale, scale));
    modelMatrix = glm::translate(modelMatrix, transform.pos);
    Mat4 projectionMatrix = camera->getMatrix() * modelMatrix;

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vertexArray);
    glUseProgram(unlitShader);

    GLuint projMatrixLocation = glGetUniformLocation(unlitShader, "projectionMatrix");
    glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, elementBuffer.size(), GL_UNSIGNED_INT, (void*)0);

    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    glBindVertexArray(GL_NONE);
    glUseProgram(GL_NONE);
}
