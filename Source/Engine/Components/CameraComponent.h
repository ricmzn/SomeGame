#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H
#include <Engine/Components/BaseComponent.h>
#include <Engine/Render/Viewport.h>

namespace Components {
class api_public CameraComponent : public BaseComponent
{
    public:
        Render::Viewport viewport;
};
}

#endif // CAMERACOMPONENT_H
