#include "Filesystem.h"
#include <sstream>

namespace Filesystem
{
    static bool fsIsInitialized = false;

    // This should probably be deprecated and done in setRootPath
    void initialize(int argc, char **argv)
    {
        if (!PHYSFS_init(argv[0]))
        {
            throw InitializationException("Could not initialize virtual filesystem!");
        }
    }

    void setRootPath(const std::string &relativeToExecutable)
    {
        // Check if PHYSFS was initialized already
        if (!PHYSFS_isInit())
        {
            throw InitializationException("Could not set paths! (Was the filesystem initialized?)");
        }

        // Build the root path
        std::string baseDir = PHYSFS_getBaseDir() + relativeToExecutable;
        // Mount the root path
        PHYSFS_mount(baseDir.c_str(), "/", 1);
        // Check for existance of MountList.txt
        if (!PHYSFS_exists("MountList.txt"))
        {
            throw InitializationException("Failed to open MountList.txt!");
        }

        // From now on, it's safe to use the filesystem classes
        fsIsInitialized = true;

        // Mount archives
        File mountList("MountList.txt");

        // Create stream objects
        std::istringstream ss(mountList.string());
        std::string line;
        // For each line
        while (std::getline(ss, line))
        {
            if (!line.empty())
            {
                // Windows CR-LF trailing CR fix
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
                    // Side-note: on most platforms, the line below copies the string twice!
                    throw InitializationException(error.str().c_str());
                }
            }
        }
    }

    bool isInit()
    {
        return fsIsInitialized;
    }
}
