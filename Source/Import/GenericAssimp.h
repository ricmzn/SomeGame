#ifndef GENERICASSIMP_H
#define GENERICASSIMP_H
#include <Import/BaseMeshImporter.h>

namespace Import
{
    class GenericAssimp : public BaseMeshImporter
    {
        public:
            void read(const char* ospath);
    };
}

#endif // GENERICASSIMP_H
