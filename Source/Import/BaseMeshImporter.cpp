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
        fwrite(&meshData, 1, sizeof(BinaryMesh), file);
    }

    const BinaryMesh& BaseMeshImporter::getMesh() const
    {
        return meshData;
    }
}
