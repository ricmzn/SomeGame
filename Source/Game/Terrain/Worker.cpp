#include "Worker.h"

namespace Terrain
{
    void Worker::threadFunction()
    {
        while (runThread)
        {
            printf(".");
        }
        printf(" Thread killed!\n");
    }

    Worker::Worker()
    {
        runThread = true;
        taskThread = Thread(&Worker::threadFunction, this);
    }

    Worker::~Worker()
    {
        runThread = false;
        taskThread.join();
    }

    void Worker::queueTask(const GenerationTask& task)
    {
        queueMutex.lock();
        pendingTasks.push(task);
        queueMutex.unlock();
    }
}
