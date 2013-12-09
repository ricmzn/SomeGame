#ifndef VIDEOMODE_H
#define VIDEOMODE_H
#include <vector>

struct videoMode
{
    int width, height;
    std::vector<int> rates;
};

typedef std::vector<videoMode> videoModeList;

/// Adds a video mode to a mode vector modeList, and if it already exists add the refresh rate to the mode. If refresh mode also exists, don't do anything.
/// @return true if mode is unique (doesn't exist in vector)
inline bool addVideoMode(videoModeList* modeList, int width, int height, int refresh)
{
    for (auto& mode : *modeList)
    {
        if (mode.width == width and mode.height == height)
        {
            for (auto& rate : mode.rates)
            {
                // Resolution and refresh rate already exist
                if (rate == refresh)
                {
                    return false;
                }
            }
            // Resolution exists but refresh rate is new
            mode.rates.push_back(refresh);
            return false;
        }
    }
    // Video mode is unique
    videoMode newMode;
    newMode.width = width;
    newMode.height = height;
    newMode.rates.push_back(refresh);
    modeList->push_back(newMode);
    return true;
}

#endif // VIDEOMODE_H
