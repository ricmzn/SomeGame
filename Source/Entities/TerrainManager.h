#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H
#include <Entities/PlayerController.h>
#include <Render/TestTerrain.h>

class TerrainManager : public Entity
{
    public:

    struct Tile
    {
        int x, y;
        bool generated;
        TestTerrain* data;
    };

    struct AsyncData
    {
        volatile int stopFlag;
        Array<Tile*> tiles;
    };

    private:
        List<Tile> tiles;
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

        float distance(const Vec3& pos, const Tile* tile) const;
        const Tile* find(int x, int y) const;
        const Tile* createTile(int x, int y);
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
