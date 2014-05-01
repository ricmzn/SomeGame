#ifndef TILE_H
#define TILE_H
#include <Base/SharedTypes.h>

class TestTerrain;

namespace Terrain
{
    class Tile
    {
        public:
            int x, y;
            bool generated;
            TestTerrain* data;
            // TODO Replace TestTerrain behavior here
    };
}

#endif // TILE_H
