#include "WorldModel.h"

void WorldModel::uploadGeometry(const BinaryMesh& mesh)
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

    vertexBuffer.upload(mesh.verts, mesh.header.nVerts * sizeof(Vec3));
    normalBuffer.upload(mesh.normals, mesh.header.nVerts * sizeof(Vec3));
    texCoordBuffer.upload(mesh.texCoords, mesh.header.nVerts * sizeof(Vec2));
    elementBuffer.upload(mesh.indices, mesh.header.nIndices * sizeof(uint32_t));

    vertexArray.setIndexArray(elementBuffer);
    vertexArray.addAttrib(vertexBuffer, 0, 3, GL_FLOAT);
    vertexArray.addAttrib(normalBuffer, 1, 3, GL_FLOAT);
    vertexArray.addAttrib(texCoordBuffer, 2, 2, GL_FLOAT);
}

WorldModel::WorldModel(const BinaryMesh& mesh)
    : vertexBuffer(GL_ARRAY_BUFFER),
      normalBuffer(GL_ARRAY_BUFFER),
      texCoordBuffer(GL_ARRAY_BUFFER),
      elementBuffer(GL_ELEMENT_ARRAY_BUFFER)
{
    this->uploadGeometry(mesh);
}
