#ifndef BASEMESHIMPORTER_H
#define BASEMESHIMPORTER_H
#include <Base/Filesystem/File.h>
#include <Base/BinaryMesh.h>

namespace Import
{
    class BaseMeshImporter
    {
        protected:
            BinaryMesh meshData;
        public:
            BaseMeshImporter();
            virtual void read(const char* ospath) = 0;
            virtual void write(const char* ospath);
            const BinaryMesh& getMesh() const;
    };
}

#endif // BASEMESHIMPORTER_H
