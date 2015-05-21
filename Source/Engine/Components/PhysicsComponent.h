#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include <Engine/Components/BaseComponent.h>

namespace Components {
struct api_public PhysicsComponent final : public BaseComponent
{
    Vec3 velocity;  // Meters per second
    Vec3 rotation;  // Radians per second
    float mass;     // Metric tons
};
}

#endif // PHYSICSCOMPONENT_H
