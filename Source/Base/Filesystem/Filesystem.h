/**
 * @defgroup Filesystem
 * @brief A small PhysFS wrapper, with misc functions/types related to files.
 *
 * @section Usage
 * PhysFS must be initialized with PHYSFS_init(argv[0]) and setRootPath(const std::string& relativeToExecutable) must be set before usage.
 *
 * See File and WriteableFile for specific class usage reference.
 * @subsection Rudimentary example
 * @code
int main(int argc, char** argv)
{
    Filesystem::initialize(argc, argv);
    // Let's assume we have a folder called myContentDirectory next to the executable
    // And in it, a file MountList.txt describes zipfile.zip in the root dir
    // In zipfile.zip: message.txt and image.png
    Filesystem::setRootPath("myContentDirectory/");
    File textFile("message.txt");
    std::cout << textFile;
    File imageFile("image.png");
    someImageLib_Image* myImage = someImageLib_loadPNG(imageFile.data(), imageFile.size());
    someImageLib_doSomething(myImage);
    // This part isn't actually in the library yet
    setWriteDir(getUserDir());
    WriteableFile logFile("log.txt");
    logFile.string("Success!\n");
    logFile.append("No errors have been found.");
    logFile.save();
    return 0;
}
 * @endcode
 * @author Ricardo Maes
 * @version 0.2.2
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "File.h"

namespace Filesystem
{
    /**
     * @ingroup Filesystem
     * @brief Convenience wrapper for PHYSFS_Init()
     * @param argc Argument count from main()
     * @param argv Arguments from main()
     */
    void initialize(int argc, char** argv);
    /**
     * @ingroup Filesystem
     * @brief This function sets the path from where all File buffers are opened from
     * @param relativeToExecutable the root path (for the application) relative to the executable
     * @note path must contain a file called MountList.txt
     */
    void setRootPath(const std::string& relativeToExecutable);
}

#endif // FILESYSTEM_H
