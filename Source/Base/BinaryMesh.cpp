#include "BinaryMesh.h"
#include <Base/NumberGenerator.h>
#include <cstring>
#define MESH_MAGIC "mdl"
#define MESH_VERSION 1

static unsigned getChecksum(const BinaryMesh* mesh)
{
    return NumberGenerator::byteSum<uint32_t>(&mesh->header,    sizeof(mesh->header))
         + NumberGenerator::byteSum<uint32_t>(mesh->verts,      mesh->header.nVerts * sizeof(Vec3))
         + NumberGenerator::byteSum<uint32_t>(mesh->texCoords,  mesh->header.nVerts * sizeof(Vec2))
         + NumberGenerator::byteSum<uint32_t>(mesh->normals,    mesh->header.nVerts * sizeof(Vec3))
         + NumberGenerator::byteSum<uint32_t>(mesh->indices,    mesh->header.nIndices * sizeof(uint32_t));
}

void BinaryMesh::initialize(BinaryMesh* mesh)
{
    memset(mesh, 0, sizeof(BinaryMesh));
    mesh->header.magic[0] = MESH_MAGIC[0];
    mesh->header.magic[1] = MESH_MAGIC[1];
    mesh->header.magic[2] = MESH_MAGIC[2];
    mesh->header.version  = MESH_VERSION;
}

void BinaryMesh::allocData(BinaryMesh *mesh)
{
    mesh->verts     = new Vec3[mesh->header.nVerts];
    mesh->texCoords = new Vec2[mesh->header.nVerts];
    mesh->normals   = new Vec3[mesh->header.nVerts];
    mesh->indices   = new uint32_t[mesh->header.nIndices];
}

void BinaryMesh::clearData(BinaryMesh *mesh)
{
    delete mesh->verts;
    delete mesh->texCoords;
    delete mesh->normals;
    delete mesh->indices;
    mesh->verts     = NULL;
    mesh->normals   = NULL;
    mesh->texCoords = NULL;
    mesh->indices   = NULL;
}

void BinaryMesh::updateChecksum(BinaryMesh* mesh)
{
    mesh->checksum = getChecksum(mesh);
}

bool BinaryMesh::isValid(const BinaryMesh* mesh)
{
    if((mesh->header.magic[0] == MESH_MAGIC[0] and
        mesh->header.magic[1] == MESH_MAGIC[1] and
        mesh->header.magic[2] == MESH_MAGIC[2]) == false)
    return false;

    if (mesh->header.version > MESH_VERSION) return false;

    if (getChecksum(mesh) != mesh->checksum) return false;

    return true;
}

void BinaryMesh::read(BinaryMesh* mesh, const Byte* src, size_t size)
{
    mesh->header = ((BinaryMesh*)src)->header;
    mesh->checksum = *((uint32_t*)(src + size - sizeof(uint32_t)));

    // TODO specialized exceptions
    if (mesh->header.magic[0] != MESH_MAGIC[0] or
        mesh->header.magic[1] != MESH_MAGIC[1] or
        mesh->header.magic[2] != MESH_MAGIC[2] or
        mesh->header.version > MESH_VERSION)
    {
        initialize(mesh);
        throw InitializationException("Invalid mesh header");
    }
    else if (mesh->checksum != NumberGenerator::byteSum<uint32_t>(src, size - sizeof(uint32_t)))
    {
        initialize(mesh);
        throw InitializationException("Invalid mesh checksum");
    }

    allocData(mesh);
    memcpy(mesh->verts,     src += sizeof(header_t),                    mesh->header.nVerts * sizeof(Vec3));
    memcpy(mesh->texCoords, src += sizeof(Vec3) * mesh->header.nVerts,  mesh->header.nVerts * sizeof(Vec2));
    memcpy(mesh->normals,   src += sizeof(Vec2) * mesh->header.nVerts,  mesh->header.nVerts * sizeof(Vec3));
    memcpy(mesh->indices,   src += sizeof(Vec3) * mesh->header.nVerts,  mesh->header.nIndices * sizeof(uint32_t));
}
