#include "TerrainManager.h"
typedef TerrainManager::Tile Tile;

TerrainManager::TerrainManager(const Camera* camera)
    : maxLod(1),
      tileWidth(256),
      tileHeight(256),
      frequency(1.0f),
      amplitude(1.0f),
      exponent(1.0f),
      octaves(1),
      camera(camera),
      workerThread(&TerrainManager::workerFunction, &workerData)
{
    workerData.stopFlag = 0;
    seed = rand();
}

TerrainManager::~TerrainManager()
{
    workerData.stopFlag = 1;
    workerThread.join();
    for (Tile& tile : tiles)
    {
        delete tile.data;
    }
}

void TerrainManager::workerFunction(AsyncData *data)
{
    while (!data->stopFlag)
    {
        // Do something with generation and stuff
    }
}

float TerrainManager::distance(const Vec3& pos, const Tile* tile) const
{
    float dist_x = pos.x - (tile->x + tileWidth/2);
    float dist_y = pos.y;
    float dist_z = pos.x - (tile->y + tileHeight/2);
    return sqrt(pow(dist_x, 2) + pow(dist_y, 2) + pow(dist_z, 2));
}

const Tile* TerrainManager::find(int x, int y) const
{
    for (const Tile& tile : tiles)
    {
        if (tile.x == x and tile.y == y)
            return &tile;
    }
    return nullptr;
}

const Tile* TerrainManager::createTile(int x, int y)
{
    Tile newTile;
    newTile.x = x;
    newTile.y = y;
    newTile.generated = false;
    newTile.data = new TestTerrain(tileWidth, tileHeight, maxLod);
    newTile.data->generate(frequency, amplitude, seed, exponent, octaves, tileWidth*x, tileHeight*y);
    tiles.push_front(newTile);
    return &tiles.front();
}

void TerrainManager::deleteTile(int x, int y)
{
    for (Tile& tile : tiles)
    {
        if (tile.x == x and tile.y == y)
        {
            delete tile.data;
            break;
        }
    }
}

void TerrainManager::spawn(SpawnFlags flags)
{
    (void)flags;
}

void TerrainManager::think(float delta)
{
    static float timeSinceLast = 60.f;
    static const int maxRange = 4;

    if (timeSinceLast > 2.f)
    {
        for (int i = -maxRange/2; i < maxRange/2; i++)
        {
            for (int j = -maxRange/2; j < maxRange/2; j++)
            {
                if (!this->find(i, j))
                {
                    this->createTile(i, j);
                }
            }
        }

        timeSinceLast = 0.f;
    }
    else
    {
        timeSinceLast += delta;
    }
}

void TerrainManager::setParams(int maxlod, int width, int height,
                               float frequency, float amplitude,
                               float exponent, int octaves)
{
    this->maxLod = maxlod;
    this->tileWidth = width;
    this->tileHeight = height;
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->exponent = exponent;
    this->octaves = octaves;
}

void TerrainManager::draw() const
{
    for (const Tile& tile : tiles)
    {
        tile.data->draw(tile.x*tileWidth,
                        0.000000f,
                        tile.y*tileHeight,
                        camera);
    }
}
