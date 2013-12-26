#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H
#include "../filesystem.h"

class MeshImporter
{
    public:
        virtual Mesh import(const File& filename) = 0;
};

#endif // MESHIMPORTER_H
