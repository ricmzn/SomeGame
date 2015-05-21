#ifndef CONTEXTOBJECT_H
#define CONTEXTOBJECT_H
#include <Engine/Base/Types/Shared.h>
#include <Engine/Render/OpenGL/Enums.hpp>

namespace Render {
class api_public ContextObject
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
