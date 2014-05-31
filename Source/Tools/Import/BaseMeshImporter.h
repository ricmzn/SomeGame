#ifndef BASEMESHIMPORTER_H
#define BASEMESHIMPORTER_H
#include <Engine/Filesystem/File.h>
#include <Engine/Base/BinaryMesh.h>

namespace Import
{
    class BaseMeshImporter
    {
        protected:
            BinaryMesh meshData;
        public:
            BaseMeshImporter();
            virtual ~BaseMeshImporter() = 0;
            virtual void read(const char* ospath) = 0;
            virtual void write(const char* ospath);
            const BinaryMesh& getMesh() const;
    };
}

#endif // BASEMESHIMPORTER_H
