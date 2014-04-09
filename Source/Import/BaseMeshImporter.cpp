#include "BaseMeshImporter.h"
#include <cstring>

namespace Import
{
    BaseMeshImporter::BaseMeshImporter()
    {
        BinaryMesh::initialize(&meshData);
    }
    BaseMeshImporter::~BaseMeshImporter()
    {
        BinaryMesh::clearData(&meshData);
    }

    void BaseMeshImporter::write(const char* ospath)
    {
        FILE* file = fopen(ospath, "wb");
        fwrite(&meshData.header,    sizeof(meshData.header), 1, file);
        fwrite(meshData.verts,      sizeof(Vec3), meshData.header.nVerts, file);
        fwrite(meshData.texCoords,  sizeof(Vec2), meshData.header.nVerts, file);
        fwrite(meshData.normals,    sizeof(Vec3), meshData.header.nVerts, file);
        fwrite(meshData.indices,    sizeof(uint32_t), meshData.header.nIndices, file);
        fwrite(&meshData.checksum,  sizeof(uint32_t), 1, file);
        fclose(file);
    }

    const BinaryMesh& BaseMeshImporter::getMesh() const
    {
        return meshData;
    }
}
