#ifndef BASEMESHIMPORTER_H
#define BASEMESHIMPORTER_H
#include <Engine/Filesystem/File.h>
#include <Engine/Base/Types/MeshFile.h>

namespace Import {
class BaseMeshImporter
{
    protected:
        Base::Types::Mesh meshData;
    public:
        BaseMeshImporter();
        virtual ~BaseMeshImporter() = 0;
        virtual void read(const char* ospath) = 0;
        virtual void write(const char* ospath);
        const Base::Types::Mesh& getMesh() const;
};
}

#endif // BASEMESHIMPORTER_H
