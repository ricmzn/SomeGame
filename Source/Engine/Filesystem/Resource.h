#ifndef FSRESOURCE_H
#define FSRESOURCE_H
#include <Engine/Base/Types/Shared.h>
#include <Engine/Filesystem/File.h>

namespace Filesystem {
class api_public Resource
{
    private:
        static HashMap<String, Resource*> pool;
    public:
        static void             prefetch(StringRef path);
        static const Resource&  request (StringRef path);
        static void             drop    (StringRef path);

    private:
        const File file;
        Resource(const File& file);
    public:
        virtual ~Resource();
        virtual void compile();
        const File& getFile() const;
    };
}
using Filesystem::Resource;

#endif // FSRESOURCE_H
