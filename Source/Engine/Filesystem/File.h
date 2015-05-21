/**
 * @ingroup Filesystem
 * @brief .
 *
 * Read the documentation on \ref Filesystem before usage.
 * @note The file's contents are held in memory until its handler is destroyed or File::clear() is called
 *
 * @author Ricardo Maes
 */

#ifndef FSFILE_H
#define FSFILE_H
#include <Engine/Filesystem/Filesystem.h>

namespace Filesystem {
class api_public File
{
    public:
        /**
         * @brief Load a file directly
         */
        File(StringRef filename);
        /**
         * @brief Alternate constructor
         */
        File(const char* filename);
        /**
         * @brief Copy constructor
         */
        File(const File& other);
        /**
         * @brief Default constructor
         */
        File();
        /**
         * @brief Destructor
         */
        virtual ~File();
        /**
         * @brief Get the size of the currently loaded file
         */
        size_t size() const;
        /**
         * @brief Get the size of any file in the current filesystem
         */
        static size_t size(StringRef path);
        /**
         * @brief Return true if a file exists, false otherwise
         */
        static bool exists(StringRef path);
        /**
         * @brief Set a file to be open
         * @param open Automatically opens the file in reading mode
         */
        void setFile(StringRef path, bool autoOpen = true);
        /**
         * @brief Open/Re-open a file that was set through setFile()
         * @param readStart first byte to read in the file
         * @param readCount maximum size to load (0 means entire file)
         * @warning if this function throws because a file is missing, previously-loaded contents are lost and must be re-loaded from the disk!
         */
        void open(size_t readStart = 0, size_t readCount = 0);
        /**
         * @brief Get the filename of the currently loaded file
         */
        String filename() const;
        /**
         * @brief Get the file's loaded content in as a text string
         */
        String toString() const;
        /**
         * @brief Get the file's loaded content in as a raw, non-null terminated byte stream
         */
        const Byte* data() const;
        /**
         * @brief Free memory taken up by the file and close it
         */
        void clear();
        /**
         * @brief Returns true if a file is open, false otherwise
         */
        explicit operator bool() const;

        File operator=(const File& other) = delete;

    protected:
        String filePath;
        size_t fileLength;
        size_t sizeLoaded;
        Byte* fileData;

        // Reads the contents of the file pointed by
        // fileHandle into dest from (start) to (start+size)
        void read(const void* file, void* dest, size_t start, size_t size);
    };
}
using Filesystem::File;

/**
 * @brief Overload of the << operator: sends data to an ostream object in string format
 */
api_public std::ostream& operator<< (std::ostream& left, const Filesystem::File& right);

//class WriteableFile : public File

#endif // FSFILE_H
