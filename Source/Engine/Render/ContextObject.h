#ifndef CONTEXTOBJECT_H
#define CONTEXTOBJECT_H
#include <Engine/Render/API.h>

namespace Render
{
    class ContextObject
    {
    protected:
        GLuint handle;

        // This stuff is non-copyable, handle with care
        ContextObject(const ContextObject& other) = delete;
        ContextObject& operator=(const ContextObject& other) = delete;

    public:
        ContextObject();
        virtual ~ContextObject() = 0;
        GLuint getHandle() const;
        operator GLuint() const;
    };
}

#endif // CONTEXTOBJECT_H
