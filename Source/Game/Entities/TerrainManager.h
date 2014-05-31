#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H
#include <Game/Entities/PlayerController.h>
#include <Game/Terrain/TestTerrain.h>
#include <Game/Terrain/Tile.h>
using Terrain::Tile;

class TerrainManager : public Entity
{
    public: struct AsyncData
    {
        volatile bool stopFlag;
        Array<Tile*> tiles;
        Mutex mutex;
    };

    private:
        Array<Tile> tiles;
        int maxLod;
        int tileWidth;
        int tileHeight;
        float frequency;
        float amplitude;
        float exponent;
        int octaves;
        int seed;
        const Camera* camera;

        AsyncData workerData;
        Thread workerThread;
        static void workerFunction(AsyncData* data);

        float distanceTile(const Vec3& pos, const Tile& tile) const;
        const Tile* findTile(int x, int y) const;
        const Tile* createTile(int x, int y, int lod);
        void deleteTile(int x, int y);

    public:
        TerrainManager(const Camera* camera);
        ~TerrainManager();
        void spawn(SpawnFlags flags);
        void think(float deltaTime);
        void setParams(int maxlod, int width, int height,
                       float frequency, float amplitude,
                       float exponent, int octaves);
        void draw() const;
};

#endif // TERRAINMANAGER_H
