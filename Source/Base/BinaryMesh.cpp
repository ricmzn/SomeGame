#include "BinaryMesh.h"
#include <Base/NumberGenerator.h>
#include <cstring>
#define MESH_MAGIC "mdl"
#define MESH_VERSION 1

static unsigned getChecksum(const BinaryMesh* mesh)
{
    return NumberGenerator::byteSum<uint32_t>(&mesh->header, sizeof(mesh->header))
         + NumberGenerator::byteSum<uint32_t>(mesh->verts, mesh->header.num_verts * sizeof(Vec4))
         + NumberGenerator::byteSum<uint32_t>(mesh->uvs, mesh->header.num_uvs * sizeof(Vec2))
         + NumberGenerator::byteSum<uint32_t>(mesh->normals, mesh->header.num_normals * sizeof(Vec4))
         + NumberGenerator::byteSum<uint32_t>(mesh->indices, mesh->header.num_indices * sizeof(Index));
}

void BinaryMesh::initialize(BinaryMesh* mesh)
{
    memset(mesh, 0, sizeof(BinaryMesh));
    mesh->header.magic[0] = MESH_MAGIC[0];
    mesh->header.magic[1] = MESH_MAGIC[1];
    mesh->header.magic[2] = MESH_MAGIC[2];
    mesh->header.version  = MESH_VERSION;
}

void BinaryMesh::prepareData(BinaryMesh *mesh)
{
    mesh->verts     = new Vec4[mesh->header.num_verts];
    mesh->uvs       = new Vec2[mesh->header.num_uvs];
    mesh->normals   = new Vec4[mesh->header.num_normals];
    mesh->indices   = new Index[mesh->header.num_indices*3];
}

void BinaryMesh::clearData(BinaryMesh *mesh)
{
    delete mesh->verts;
    delete mesh->uvs;
    delete mesh->normals;
    delete mesh->indices;
    mesh->verts     = NULL;
    mesh->normals   = NULL;
    mesh->uvs       = NULL;
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
    // TODO verify the checksum before reading the file (checksum is always at [size - 4])
    mesh->header = ((BinaryMesh*)src)->header;
    prepareData(mesh);

    memcpy(mesh->verts,     src += sizeof(header_t),                        mesh->header.num_verts * sizeof(Vec4));
    memcpy(mesh->uvs,       src += sizeof(Vec4) * mesh->header.num_verts,   mesh->header.num_uvs * sizeof(Vec2));
    memcpy(mesh->normals,   src += sizeof(Vec2) * mesh->header.num_uvs,     mesh->header.num_normals * sizeof(Vec4));
    memcpy(mesh->indices,   src += sizeof(Vec4) * mesh->header.num_normals, mesh->header.num_indices * sizeof(Index) * 3);

    mesh->checksum = *((uint32_t*)(src += sizeof(Index) * mesh->header.num_indices));
}
