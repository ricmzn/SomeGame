#include "BaseMeshImporter.h"

namespace Importers
{
    void BaseMeshImporter::write(const char* destination)
    {

    }

    const BinaryMesh& BaseMeshImporter::getMesh() const
    {
        return meshData;
    }
}
