#include "BaseMeshImporter.h"
#include <cstring>
using namespace Import;

BaseMeshImporter::BaseMeshImporter()
{
    Base::Types::Mesh::initialize(&meshData);
}

BaseMeshImporter::~BaseMeshImporter()
{
    Base::Types::Mesh::clearData(&meshData);
}

void BaseMeshImporter::write(const char* ospath)
{
    if(meshData.header.nVerts > 0) {
        FILE* file = fopen(ospath, "wb");
        fwrite(&meshData.header,    sizeof(meshData.header), 1, file);
        fwrite(meshData.verts,      sizeof(Vec3), meshData.header.nVerts, file);
        fwrite(meshData.texCoords,  sizeof(Vec2), meshData.header.nVerts, file);
        fwrite(meshData.normals,    sizeof(Vec3), meshData.header.nVerts, file);
        fwrite(meshData.indices,    sizeof(uint32_t), meshData.header.nIndices, file);
        fwrite(&meshData.checksum,  sizeof(uint32_t), 1, file);
        fclose(file);
    }
}

const Base::Types::Mesh& BaseMeshImporter::getMesh() const
{
    return meshData;
}
