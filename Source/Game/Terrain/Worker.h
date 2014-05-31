#ifndef WORKER_H
#define WORKER_H
#include <Engine/Base/SharedTypes.h>
#include <Game/Terrain/Tile.h>

namespace Terrain
{
    struct GenerationTask
    {
        int posx, posy;
        int lod, width, height;
        int octaves, seed;
        float freq, exp;
    };

    class Worker
    {
        private:
            Queue<GenerationTask> pendingTasks;
            Array<Tile> generatedTiles;
            Thread taskThread;
            Mutex queueMutex;
            volatile bool runThread;
            void threadFunction();
        public:
            Worker();
            ~Worker();
            void queueTask(const GenerationTask& task);
    };
}

#endif // WORKER_H
