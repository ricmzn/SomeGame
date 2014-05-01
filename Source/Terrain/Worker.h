#ifndef WORKER_H
#define WORKER_H
#include <Base/SharedTypes.h>
#include <Terrain/Tile.h>

namespace Terrain
{
    struct GenerationTask
    {
        int posx, posy;
        int lod, width, height;
        int octaves, seed;
        float freq, exp;
        Array<Tile>* dest;
    };

    class Worker
    {
        private:
            Queue<GenerationTask> pendingTasks;
            Thread taskWorkerThread;
            void threadFunction();
        public:
            Worker();
            ~Worker();
            void queueTask(const GenerationTask& task);
    };
}

#endif // WORKER_H
