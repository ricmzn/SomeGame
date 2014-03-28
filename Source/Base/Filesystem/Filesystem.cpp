#include "Filesystem.h"

namespace Filesystem
{
    void initialize(int argc, char **argv)
    {
        if (!PHYSFS_isInit())
            PHYSFS_init(argv[0]);
    }

    void setRootPath(const std::string &relativeToExecutable)
    {
        std::string BaseDir = PHYSFS_getBaseDir() + relativeToExecutable;
        PHYSFS_mount(BaseDir.c_str(), "/", 1);
        // TODO Check for existance of MountList.txt and parse it
        // to mount any .zip file paths contained
    }
}
