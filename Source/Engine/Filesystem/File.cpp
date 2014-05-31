#include "File.h"
#include <Engine/Base/Exceptions.h>
#include <iostream>
#include <vector>
using namespace Exceptions;

File::File(const std::string& filename)
{
    // Might want to check if the filesystem is initialized
    if(!Filesystem::isInit())
    {
        throw GenericError("Filesystem is not initialized!");
    }

    fileHandle = nullptr;
    fileData = nullptr;
    setFile(filename);
}

File::File(const char* filename) : File(std::string(filename)) {}
File::File() : File("") {}

File::~File()
{
    if(fileHandle != nullptr)
    {
        PHYSFS_close(fileHandle);
    }
    if(fileData != nullptr)
    {
        delete[] fileData;
    }
}

unsigned File::size() const
{
    if(fileHandle != nullptr)
    {
        return fileLength;
    }
    else
    {
        return 0;
    }
}

unsigned File::size(const std::string& file)
{
    unsigned tempSize;
    PHYSFS_File *temp = PHYSFS_openRead(file.c_str());
    tempSize = PHYSFS_fileLength(temp);
    PHYSFS_close(temp);
    return tempSize;
}

void File::setFile(const std::string& file)
{
    if(file == "")
    {
        clear();
    }
    else
    {
        clear();
        if(!openFile(file))
        {
            // File probably does not exist
            throw MissingFile(file.c_str());
        }
        if(fileData != nullptr)
        {
            delete[] fileData;
        }
        fileData = new unsigned char[fileLength];
        readData(fileData, 0, fileLength);
    }
}

std::string File::filename() const
{
    return filePath;
}

std::string File::toString() const
{
    if(fileData != nullptr)
    {
        return std::string((const char*)fileData, fileLength);
    }
    else
    {
        return std::string("");
    }
}

const unsigned char* File::data() const
{
    return fileData;
}

void File::clear()
{
    if(fileHandle != nullptr)
    {
        PHYSFS_close(fileHandle);
        fileHandle = nullptr;
    }
    filePath.clear();
    if(fileData != nullptr)
    {
        delete[] fileData;
        fileData = nullptr;
    }
}

void File::close()
{
    if(fileHandle != nullptr)
    {
        PHYSFS_close(fileHandle);
        fileHandle = nullptr;
    }
}

File::operator bool() const
{
    return(fileHandle != nullptr);
}

const PHYSFS_File* File::getHandle() const
{
    return fileHandle;
}

bool File::openFile(const std::string& filename, bool writeMode)
{
    if(!PHYSFS_exists(filename.c_str()))
    {
        clear();
        return false;
    }
    if(writeMode)
    {
        fileHandle = PHYSFS_openWrite(filename.c_str());
    }
    else
    {
        fileHandle = PHYSFS_openRead(filename.c_str());
    }
    fileLength = PHYSFS_fileLength(fileHandle);
    filePath = filename;
    return true;
}

void File::readData(void* dest, size_t start, size_t sz)
{
    if(fileHandle == nullptr)
    {
        std::cerr << "Fatal error: file wasn't opened before trying to read from it!\n";
        return;
    }
    PHYSFS_seek(fileHandle, start);
    PHYSFS_read(fileHandle, dest, sz, 1);
    PHYSFS_seek(fileHandle, 0);
}

std::ostream& operator<<(std::ostream& left, const File& right)
{
    left << right.toString();
    return left;
}
