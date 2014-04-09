/**
 * @ingroup Filesystem
 * @brief .
 *
 * Read the documentation on \ref Filesystem before usage.
 * @note The entire file is kept in memory until it's destroyed or cleared.
 * @todo Stream large files
 *
 * @author Ricardo Maes
 */

#ifndef FILE_H
#define FILE_H
#include <Base/Filesystem/Filesystem.h>
#include <physfs.h>
#include <string>

class File
{
    public:
        /**
         * @brief Filename constructor. Creates a File object and loads the specified file directly
         */
        File(const std::string& filename);
        /**
         * @brief Alternate filename constructor
         */
        File(const char* filename);
        /**
         * @brief Default constructor. Does not load any files, any calls to its member functions will return empty
         */
        File();
        /**
         * @brief Destructor. Releases the file handle and kills the data in memory
         */
        virtual ~File();
        /**
         * @brief Get the size of the currently loaded file
         */
        unsigned size() const;
        /**
         * @brief Get the size of any file in the current filesystem
         */
        static unsigned size(const std::string& file);
        /**
         * @brief Clears the content of the object and loads a new file into it
         */
        void setFile(const std::string& file);
        /**
         * @brief Get the filename of the currently loaded file
         */
        std::string filename() const;
        /**
         * @brief Get the file's loaded content in as a text string
         */
        std::string string() const;
        /**
         * @brief Get the file's loaded content in as a raw, non-null terminated byte stream
         */
        const char* data() const;
        /**
         * @brief Get the handle used to read the file
         */
        const PHYSFS_File* getHandle() const;
        /**
         * @brief Clear the file's content in memory and release it
         */
        void clear();
        /**
         * @brief Close the file handle but keep it in memory
         */
        void close();
        /**
         * @brief Returns true if a file is open, false otherwise
         */
        explicit operator bool() const;

    protected:
        PHYSFS_File* fileHandle;
        std::string filePath;
        size_t fileLength;
        char* fileData;

        bool openFile(const std::string& filename, bool writeMode = false);
        void readData(void* dest, size_t start, size_t size);
};

/**
 * @brief Overload of the << operator: sends data to an ostream object in string format
 */
std::ostream& operator<< (std::ostream& left, const File& right);

//class WriteableFile : public File

#endif // FILE_H
