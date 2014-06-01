#include "StaticModel.h"
#include <Engine/Filesystem/File.h>

StaticModel::StaticModel(const char* filename, Vec3 pos)
{
    BinaryMesh mesh;
    File file(filename);
    BinaryMesh::read(&mesh, file.data(), file.size());
    this->setMesh(&mesh);
    this->transform.pos = pos;
    BinaryMesh::clearData(&mesh);
}

void StaticModel::spawn()
{}

void StaticModel::think()
{}
