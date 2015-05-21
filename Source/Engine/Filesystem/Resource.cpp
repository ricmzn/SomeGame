#include "Resource.h"
#define PREFETCH_SIZE 128*1024
using namespace Filesystem;

HashMap<String, Resource*> Resource::pool;

const Resource& Resource::request(StringRef path)
{
    Resource* resource;
    auto iter = pool.find(path);
    if(iter != pool.end()) {
        resource = iter->second;
    } else {
        resource = new Resource(path);
        pool.emplace(path, resource);
    }
    return *resource;
}

void Resource::drop(StringRef path)
{
    auto it = pool.find(path);
    if (it != pool.end()) {
        delete it->second;
        pool.erase(it);
    }
}

Resource::Resource(const File& file)
    : file(file)
{
}

Resource::~Resource()
{
}

void Resource::compile()
{
}

const File& Resource::getFile() const
{
    return file;
}
