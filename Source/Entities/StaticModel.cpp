#include "StaticModel.h"
#include <Base/Filesystem/File.h>

StaticModel::StaticModel(const char* filename, Vec3 pos)
{
    BinaryMesh mesh;
    File file(filename);
    BinaryMesh::read(&mesh, file.data(), file.size());
    this->setMesh(&mesh);
    this->transform.pos = pos;
}

void StaticModel::spawn(SpawnFlags flags)
{
    (void)flags;
}

void StaticModel::think(float deltaTime)
{
    (void)deltaTime;
}
