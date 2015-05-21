#ifndef SCENECOMPONENT
#define SCENECOMPONENT
#include <Engine/Components/BaseComponent.h>
#include <Engine/Render/Scene.h>

namespace Components {
class api_public SceneComponent : public BaseComponent
{
    public:
        virtual void draw(Render::Scene* scene) = 0;
};
}

#endif // SCENECOMPONENT
