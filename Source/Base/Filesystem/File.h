#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED
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
    PHYSFS_init(argv[0]);
    // Let's assume we have a folder called myContentDirectory next to the executable
    // And inside of this folder there is files.zip with message.txt and image.png
    setRootPath("myContentDirectory/");
    PHYSFS_mount("files.zip", false);
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
 * @version 0.2.1-nosfml
 */
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <physfs.h>

/**
 * @ingroup Filesystem
 * @brief This function sets the path from where all File buffers are opened from
 * @param relativeToExecutable the root path (for the application) relative to the executable
 */
void setRootPath(const std::string& relativeToExecutable);

/**
 * @ingroup Filesystem
 * @brief A simple file.
 *
 * Read the documentation on filesystem.h before usage.
 * @note The entire file is loaded in memory at once.
 *
 * Example:
 * @code
 * File myFile;
 * // We set our file buffer to myFile.txt
 * myFile.setFile("myFile.txt");
 * // Then we copy the data to a string
 * std::string myString = myFile.string();
 * // And use it as we want
 * std::cout << myString << std::endl;
 * @endcode
 * @author Ricardo Maes
 */
class File
{
    public:
        /**
         * Filename constructor. Creates a File object and loads the specified file directly.
         */
        File(const std::string& filename);
        /**
         * Alternate filename constructor.
         */
        File(const char* filename);
        /**
         * Default constructor. Does not load any files, any calls to its member functions will return empty.
         */
        File();
        /**
         * Destructor. Releases the file handle and kills the data in memory.
         */
        virtual ~File();
        /**
         * Get the size of the currently loaded file.
         */
        unsigned size() const;
        /**
         * Get the size of any file in the current filesystem.
         */
        static unsigned size(const std::string& file);
        /**
         * Clears the content of the object and loads a new file into it.
         */
        bool setFile(const std::string& file);
        /**
         * Get the filename of the currently loaded file.
         */
        std::string filename() const;
        /**
         * Get the file's loaded content in as a text string.
         */
        // TODO Encoding and line ending conversions
        std::string string() const;
        /**
         * Get the file's loaded content in as a raw, non-null terminated byte stream.
         */
        const char* data() const;
        /**
         * Get the handle used to read the file
         */
        const PHYSFS_File* getHandle();
        /**
         * Clear the file's content in memory and release it.
         */
        void clear();
        /**
         * Close the file handle but keep it in memory.
         */
        void close();

    protected:
        PHYSFS_File* fileHandle;
        std::string filePath;
        size_t fileLength;
        char *fileData;

        bool openFile(const std::string& filename, bool writeMode = false);
        void readData(void* dest, size_t start, size_t size);
};

/**
 * Overload of the << operator: sends data to an ostream object in string format.
 */
std::ostream& operator<< (std::ostream& left, const File& right);

//class WriteableFile : public File

#endif
