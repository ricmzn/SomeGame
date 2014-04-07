#include "BaseMeshImporter.h"
#include <cstring>

namespace Importers
{
    BaseMeshImporter::BaseMeshImporter()
    {
        BinaryMesh::initialize(&meshData);
    }

    void BaseMeshImporter::write(const char* destination)
    {
        BinaryMesh::updateChecksum(&meshData);
        FILE* file = fopen(destination, "wb");
        fwrite(&meshData.header, sizeof(meshData.header), 1, file);
        fwrite(meshData.verts, sizeof(Vec4), meshData.header.num_verts, file);
        fwrite(meshData.uvs, sizeof(Vec2), meshData.header.num_uvs, file);
        fwrite(meshData.normals, sizeof(Vec4), meshData.header.num_normals, file);
        fwrite(meshData.indices, sizeof(Index), meshData.header.num_indices * 3, file);
        fwrite(&meshData.checksum, sizeof(uint32_t), 1, file);
        fclose(file);
    }

    const BinaryMesh& BaseMeshImporter::getMesh() const
    {
        return meshData;
    }
}
