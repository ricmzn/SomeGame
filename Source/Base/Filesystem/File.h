#ifndef FILE_H
#define FILE_H
#include <physfs.h>
#include <string>

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

#endif // FILE_H
