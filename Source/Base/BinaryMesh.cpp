#include "BinaryMesh.h"
#include <Base/NumberGenerator.h>
#include <cstring>

void BinaryMesh::initialize(BinaryMesh* mesh)
{
    memset(mesh, 0, sizeof(BinaryMesh));
    mesh->magic[0] = 'm';
    mesh->magic[1] = 'd';
    mesh->magic[2] = 'l';
    mesh->version = 1;
}

void BinaryMesh::updateChecksum(BinaryMesh* mesh)
{
    mesh->checksum = NumberGenerator::byteSum<uint32_t>(mesh, sizeof(*mesh) - sizeof(mesh->checksum));
}

bool BinaryMesh::isValid(const BinaryMesh* mesh)
{
    if((mesh->magic[0] == 'm' and
        mesh->magic[1] == 'd' and
        mesh->magic[2] == 'l') == false)
    return false;

    if (mesh->version > 1) return false;

    if (NumberGenerator::byteSum<uint32_t>(mesh, sizeof(*mesh) - sizeof(mesh->checksum))
        != mesh->checksum) return false;

    return true;
}
