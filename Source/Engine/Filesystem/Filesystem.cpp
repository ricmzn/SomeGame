#include "Filesystem.h"
#include <Engine/System/Application.h>
#include <Engine/Base/Exceptions.h>
#include <sstream>

namespace Filesystem
{
    static bool fsIsInitialized = false;

    void setRootPath(const std::string &relativeToExecutable)
    {
        if (!PHYSFS_isInit())
        {
            // Initialize PHYSFS before using it
            PHYSFS_init(mainPath);
        }

        // Build the root path
        std::string baseDir = PHYSFS_getBaseDir() + relativeToExecutable;
        // Mount the root path
        PHYSFS_mount(baseDir.c_str(), "/", 1);
        // Check for existance of MountList.txt
        if (!PHYSFS_exists("MountList.txt"))
        {
            throw GenericError("Failed to open MountList.txt!");
        }

        // From now on, it's safe to use the filesystem classes
        fsIsInitialized = true;

        // Mount archives
        File mountList("MountList.txt");

        // Create stream objects
        std::istringstream ss(mountList.toString());
        std::string line;
        // For each line
        while (std::getline(ss, line))
        {
            if (!line.empty())
            {
                // Get rid of the carriage return at the end of the line
                if (line.at(line.size()-1) == '\r')
                {
                    line.resize(line.size()-1);
                }

                // Build the mount path
                std::string mountPath = baseDir + "/" + line;
                // Mount the file
                int status = PHYSFS_mount(mountPath.c_str(), "/", 0);
                // Abort if the path couldn't be mounted
                if(!status)
                {
                    std::stringstream error;
                    error << "Tried to mount invalid path/archive: \'" << line << "\'";
                    throw GenericError(error.str().c_str());
                }
            }
        }
    }

    bool isInit()
    {
        return fsIsInitialized;
    }
}
