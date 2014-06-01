#include "TerrainManager.h"
#include <Engine/System/Application.h>

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
    workerData.stopFlag = false;
    seed = rand();
}

TerrainManager::~TerrainManager()
{
    workerData.stopFlag = true;
    workerThread.join();
    for (Tile& tile : tiles)
    {
        delete tile.data;
    }
}

void TerrainManager::workerFunction(AsyncData* data)
{
    while (!data->stopFlag)
    {
        data->mutex.lock();
        while (data->tiles.size())
        {
            data->tiles.pop_back();
        }
        data->mutex.unlock();
    }
}

float TerrainManager::distanceTile(const Vec3& pos, const Tile& tile) const
{
    float dist_x = pos.x - (tile.x * tileWidth);
    float dist_y = pos.y;
    float dist_z = pos.z - (tile.y * tileHeight);
    return sqrt(pow(dist_x, 2) + pow(dist_y, 2) + pow(dist_z, 2));
}

const Tile* TerrainManager::findTile(int x, int y) const
{
    for (const Tile& tile : tiles)
    {
        if (tile.x == x and tile.y == y)
            return &tile;
    }
    return nullptr;
}

const Tile* TerrainManager::createTile(int x, int y, int lod)
{
    Tile newTile;
    newTile.x = x;
    newTile.y = y;
    newTile.generated = false;
    newTile.data = new TestTerrain(tileWidth, tileHeight, lod);
    newTile.data->generate(frequency, amplitude, seed, exponent, octaves, tileWidth*x, tileHeight*y);
    tiles.push_back(newTile);
    newTile.generated = true;
    return &tiles.back();
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

void TerrainManager::spawn()
{}

void TerrainManager::think()
{
    static float timeSinceLast = 60.f;
    static const int maxRange = 2;

    if (timeSinceLast > 0.25f)
    {
        for (int i = -maxRange; i < maxRange; i++)
        {
            for (int j = -maxRange; j < maxRange; j++)
            {
                if (!findTile(i, j))
                {
                    createTile(i, j, maxLod);
                }
            }
        }

        timeSinceLast = 0.f;
    }
    else
    {
        timeSinceLast += mainApp->deltaTime;
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
