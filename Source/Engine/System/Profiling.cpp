#include "Profiling.h"
using namespace System;

void ApplicationProfiler::addTime(StringRef category, Tick time)
{
    lastFrame[category] = time;
    total[category]    += time;
}

Tick ApplicationProfiler::getFrameTime(StringRef category) const
{
    const auto& iter = lastFrame.find(category);
    if (iter != lastFrame.end()) {
        return iter->second;
    }
    else {
        return 0;
    }
}

Tick ApplicationProfiler::getTotalTime(StringRef category) const
{
    const auto& iter = lastFrame.find(category);
    if (iter != lastFrame.end()) {
        return iter->second;
    }
    else {
        return 0;
    }
}

void ApplicationProfiler::forEachFrame(void (*function)(StringRef key, Tick value))
{
    for (auto& pair : lastFrame) {
        function(pair.first, pair.second);
    }
}

void ApplicationProfiler::forEachTotal(void (*function)(StringRef key, Tick value))
{
    for (auto& pair : total) {
        function(pair.first, pair.second);
    }
}

void ApplicationProfiler::clearCurrentFrame()
{
    lastFrame.erase(lastFrame.begin(), lastFrame.end());
}

void ApplicationProfiler::clearAllFrames()
{
    lastFrame.erase(lastFrame.begin(), lastFrame.end());
    total.erase(total.begin(), total.end());
}

///////////////////
// ScopeProfiler //
///////////////////

ScopeProfiler::ScopeProfiler(ApplicationProfiler& profiler, StringRef category)
    : profiler(profiler),
      category(category),
      start(Time::getNanoseconds())
{}

ScopeProfiler::~ScopeProfiler()
{
    end = Time::getNanoseconds();
    profiler.addTime(category, end - start);
}
