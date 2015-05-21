#ifndef FSFILESYSTEM_H
#define FSFILESYSTEM_H
#include <Engine/System/Macros.h>
#include <Engine/Base/Types/Shared.h>
#include "File.h"

namespace Filesystem
{
    /**
     * @brief Sets the root of the virtual filesystem. MountList.txt must exist in the path
     *
     * MountList.txt is required both for safety (so it cannot mount a non-game folder if the executable
     * is moved) and also to specify .zip files which should be mounted.
     *
     * If unused, MountList.txt can be left empty
     *
     * @param relativeToExecutable the root path (for the application) relative to the executable
     * @throws InitializationException if Filesystem::initialize() was not called first
     * @throws InitializationException if MountList.txt does not exist in the given path
     * @throws InitializationException if an archive listed in MountList.txt does not exist
     */
    api_public void setRootPath(StringRef relativeToExecutable);
    /**
     * @return true if setRootPath() was called and ran successfully
     */
    api_public bool isInit();
}

#endif // FSFILESYSTEM_H
