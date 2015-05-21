#include "File.h"
#include <Engine/Base/Exceptions.h>
#include <physfs.h>
#include <cstring>

File::File(StringRef path)
{
    fileLength = 0;
    fileData = nullptr;
    setFile(path);
}

File::File(const char* filename)
    : File(String(filename)) {}

File::File(const File& other)
    : File(other.filename()) {}

File::File()
    : File("") {}

File::~File()
{
    if(fileData) {
        delete[] fileData;
    }
}

size_t File::size() const
{
    return fileLength;
}

size_t File::size(StringRef path)
{
    if (File::exists(path)) {
        size_t size;
        PHYSFS_File* handle = PHYSFS_openRead(path.c_str());
        size = PHYSFS_fileLength(handle);
        PHYSFS_close(handle);
        return size;
    } else {
        throw MissingFile(path.c_str());
    }
}

bool File::exists(StringRef path)
{
    return PHYSFS_exists(path.c_str()) != 0;
}

void File::setFile(StringRef path, bool autoOpen)
{
    if(path.empty()) {
        this->clear();
        return;
    }

    if(File::exists(path)) {
        filePath = path;
        if (autoOpen) {
            this->open();
        }
    } else {
        throw MissingFile(path.c_str());
    }
}

void File::open(size_t readStart, size_t readCount)
{
    if(!Filesystem::isInit()) {
        throw GenericError("Filesystem is not initialized!");
    }

    this->clear();
    if(exists(filePath)) {
        PHYSFS_File* file = PHYSFS_openRead(filePath.c_str());
        fileLength = PHYSFS_fileLength(file);
        if (readCount == 0) {
            readCount = fileLength;
        }
        fileData = new Byte[fileLength];
        this->read(file, fileData, readStart, readCount);
        PHYSFS_close(file);
    } else {
        throw MissingFile(filePath.c_str());
    }
}

String File::filename() const
{
    return filePath;
}

String File::toString() const
{
    if(fileData) {
        return String((const char*)fileData, fileLength);
    }
    else {
        return String("");
    }
}

const Byte* File::data() const
{
    return fileData;
}

void File::clear()
{
    if(fileData) {
        delete[] fileData;
        fileData = nullptr;
    }
    fileLength = 0;
}

File::operator bool() const
{
    return fileLength > 0;
}

void File::read(const void* file, void* dest, size_t start, size_t size)
{
    PHYSFS_File* filePtr = (PHYSFS_File*)file;
    if(filePtr) {
        PHYSFS_seek(filePtr, start);
        PHYSFS_read(filePtr, dest, size, 1);
        PHYSFS_seek(filePtr, 0);
    }
}

std::ostream& operator<<(std::ostream& left, const File& right)
{
    left << right.toString();
    return left;
}
