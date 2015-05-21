#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include <Engine/Base/Types/Shared.h>

namespace Components {
struct api_public BaseComponent
{
    virtual ~BaseComponent() {}
};
}

#endif // BASECOMPONENT_H
