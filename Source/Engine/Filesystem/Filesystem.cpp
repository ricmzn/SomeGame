#include "Filesystem.h"
#include <Engine/Base/Application.h>
#include <Engine/Base/Exceptions.h>
#include <physfs.h>
#include <sstream>

namespace Filesystem
{
    using std::stringstream;

    static bool fsIsInitialized = false;

    void setRootPath(StringRef relativeToExecutable)
    {
        if (!PHYSFS_isInit()) {
            // Initialize PHYSFS before using it
            PHYSFS_init(Base::applicationPath);
        }

        // Build the root path
        String baseDir = PHYSFS_getBaseDir() + relativeToExecutable;
        // Mount the root path
        PHYSFS_mount(baseDir.c_str(), "/", 1);
        // Check for existance of MountList.txt
        if (!PHYSFS_exists("MountList.txt")) {
            throw GenericError("Failed to open MountList.txt!");
        }

        // From now on, it's safe to use the filesystem classes
        fsIsInitialized = true;

        // Mount archives
        File mountList("MountList.txt");

        // Create stream objects
        stringstream ss(mountList.toString());
        String line;
        // For each line
        while (std::getline(ss, line)) {
            if (!line.empty()) {
                // Get rid of the carriage return at the end of the line
                if (line.at(line.size()-1) == '\r') {
                    line.resize(line.size()-1);
                }

                // Build the mount path
                String mountPath = baseDir + "/" + line;
                // Mount the file
                int status = PHYSFS_mount(mountPath.c_str(), "/", 0);
                // Abort if the path couldn't be mounted
                if(!status) {
                    stringstream error;
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
