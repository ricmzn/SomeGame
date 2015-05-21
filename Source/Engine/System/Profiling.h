#ifndef APPLICATIONPROFILER_H
#define APPLICATIONPROFILER_H
#include <Engine/Base/Types/Shared.h>
#include <Engine/System/Macros.h>
#include <Engine/System/Time.h>

namespace System {
class api_public ApplicationProfiler
{
    private:
        typedef HashMap<String, Tick> TimeTable;
        TimeTable lastFrame;
        TimeTable total;

    public:
        void addTime(StringRef category, Tick time);
        Tick getFrameTime(StringRef category) const;
        Tick getTotalTime(StringRef category) const;
        void forEachFrame(void (*function)(StringRef key, Tick value));
        void forEachTotal(void (*function)(StringRef key, Tick value));
        void clearCurrentFrame();
        void clearAllFrames();
};

class api_public ScopeProfiler
{
    private:
        ApplicationProfiler& profiler;
        String category;
        Tick start, end;
    public:
        ScopeProfiler(ApplicationProfiler& profiler, StringRef category);
        ~ScopeProfiler();
};
}

using System::ScopeProfiler;

#endif // APPLICATIONPROFILER_H
