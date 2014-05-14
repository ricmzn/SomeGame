/**
 * @defgroup Filesystem
 * @brief A small PhysFS wrapper, with misc functions/types related to files.
 *
 * @section Usage
 * Initialization:
@code
    Filesystem::initialize(argc, argv);
    Filesystem::setRootPath("../Data"); // Primary folder from where files are opened, can be anything
@endcode
 * Opening a file:
@code
    File myFile1("file1.txt");

    // Or
    File myFile2;
    myFile2.setFile("file2.txt");
@endcode
 * Using the data:
@code
    std::string myString = myFile1.string();
    doSomething(myString);

    // Or
    doSomething(myFile2.data(), myFile2.size());
@endcode
 * Closing a file:
@code
// Frees the handle but keeps the data for reading
myFile1.close();

// Frees the handle and deallocates the data
myFile2.clear();
@endcode
 *
 * @see File
 *
 * @author Ricardo Maes
 * @version 0.2.2_1
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include "File.h"

namespace Filesystem
{
    /**
     * @ingroup Filesystem
     * @brief Convenience wrapper for PHYSFS_Init()
     * @param argc Argument count from main()
     * @param argv Arguments from main()
     * @throws InitializationException if PHYSFS fails to initialize
     */
    void initialize(int argc, char** argv);
    /**
     * @ingroup Filesystem
     * @brief Sets the root of the virtual filesystem. MountList.txt must exist in the path
     *
     * MountList.txt is required both for safety (so it cannot mount a non-game folder if the executable
     * is moved) and is also used to specify .zip files which can be mounted alongside the given path.
     * The file may be empty if desired.
     *
     * @param relativeToExecutable the root path (for the application) relative to the executable
     * @throws InitializationException if Filesystem::initialize() was not called first
     * @throws InitializationException if MountList.txt does not exist in the given path
     * @throws InitializationException if an archive listed in MountList.txt does not exist
     */
    void setRootPath(const std::string& relativeToExecutable);
    /**
     * @ingroup Filesystem
     * @return true if initialize() and setRootPath() were called and succeeded, false otherwise.
     */
    bool isInit();
}

#endif // FILESYSTEM_H
