#ifndef WAVEFRONTOBJ_H
#define WAVEFRONTOBJ_H
#include <Import/BaseMeshImporter.h>

namespace Importers
{
    class WavefrontObj : public BaseMeshImporter
    {
        public:
            int unfinished;
            WavefrontObj() {unfinished = 4;}
            void read(const char *filename);
    };
}

#endif // WAVEFRONTOBJ_H
