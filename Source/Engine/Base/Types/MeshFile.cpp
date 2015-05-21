#include "MeshFile.h"
#include <Engine/Base/NumberGenerator.h>
#include <Engine/Base/Exceptions.h>
#include <cstring>
using namespace Base::Types;

#define MESH_MAGIC "mdl"
#define MESH_VERSION 1

static unsigned getChecksum(const Mesh* mesh)
{
    return Base::NumberGenerator::byteSum(mesh->header)
         + Base::NumberGenerator::byteSum(mesh->verts,      mesh->header.nVerts * sizeof(Vec3))
         + Base::NumberGenerator::byteSum(mesh->texCoords,  mesh->header.nVerts * sizeof(Vec2))
         + Base::NumberGenerator::byteSum(mesh->normals,    mesh->header.nVerts * sizeof(Vec3))
         + Base::NumberGenerator::byteSum(mesh->indices,    mesh->header.nIndices * sizeof(uint32_t));
}

void Mesh::initialize(Mesh* mesh)
{
    memset(mesh, 0, sizeof(Mesh));
    mesh->header.magic[0]   = MESH_MAGIC[0];
    mesh->header.magic[1]   = MESH_MAGIC[1];
    mesh->header.magic[2]   = MESH_MAGIC[2];
    mesh->header.version    = MESH_VERSION;
    mesh->verts     = NULL;
    mesh->normals   = NULL;
    mesh->texCoords = NULL;
    mesh->indices   = NULL;
}

void Mesh::allocData(Mesh* mesh)
{
    mesh->verts     = new Vec3[mesh->header.nVerts];
    mesh->texCoords = new Vec2[mesh->header.nVerts];
    mesh->normals   = new Vec3[mesh->header.nVerts];
    mesh->indices   = new uint32_t[mesh->header.nIndices];
}

void Mesh::clearData(Mesh* mesh)
{
    if (mesh->verts)        delete[] mesh->verts;
    if (mesh->normals)      delete[] mesh->texCoords;
    if (mesh->texCoords)    delete[] mesh->normals;
    if (mesh->indices)      delete[] mesh->indices;
    mesh->verts     = NULL;
    mesh->normals   = NULL;
    mesh->texCoords = NULL;
    mesh->indices   = NULL;
}

void Mesh::updateChecksum(Mesh* mesh)
{
    mesh->checksum = getChecksum(mesh);
}

bool Mesh::isValid(const Mesh* mesh)
{
    if((mesh->header.magic[0] == MESH_MAGIC[0] and
        mesh->header.magic[1] == MESH_MAGIC[1] and
        mesh->header.magic[2] == MESH_MAGIC[2]) == false)
    return false;

    if (mesh->header.version > MESH_VERSION) return false;

    if (getChecksum(mesh) != mesh->checksum) return false;

    return true;
}

void Mesh::read(Mesh* mesh, const Byte* src, size_t size)
{
    mesh->header = ((Mesh*)src)->header;
    mesh->checksum = *((uint32_t*)(src + size - sizeof(uint32_t)));

    // TODO: Specialized file consistency exceptions
    if (mesh->header.magic[0] != MESH_MAGIC[0] or
        mesh->header.magic[1] != MESH_MAGIC[1] or
        mesh->header.magic[2] != MESH_MAGIC[2] or
        mesh->header.version > MESH_VERSION)
    {
        initialize(mesh);
        throw GenericError("Invalid mesh header");
    }
    else if (mesh->checksum != NumberGenerator::byteSum(src, size - sizeof(uint32_t)))
    {
        initialize(mesh);
        throw GenericError("Invalid mesh checksum");
    }

    allocData(mesh);
    memcpy(mesh->verts,     src += sizeof(header_t),                    mesh->header.nVerts * sizeof(Vec3));
    memcpy(mesh->texCoords, src += sizeof(Vec3) * mesh->header.nVerts,  mesh->header.nVerts * sizeof(Vec2));
    memcpy(mesh->normals,   src += sizeof(Vec2) * mesh->header.nVerts,  mesh->header.nVerts * sizeof(Vec3));
    memcpy(mesh->indices,   src += sizeof(Vec3) * mesh->header.nVerts,  mesh->header.nIndices * sizeof(uint32_t));
}
