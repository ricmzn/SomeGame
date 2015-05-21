#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include <Engine/Components/BaseComponent.h>

namespace Components {
class api_public TransformComponent : public BaseComponent
{
    public:
        Vec3 position;  // Meters from relative center
        Quat rotation;  // Radians around axis
        Vec3 scale;     // Scale multiplier

        void translate(const Vec3& translation);
        void rotate(const Vec3& axis, float angle);
        void rescale(const Vec3& factor);

        Vec3 getForwardVector() const;
        Vec3 getRightVector() const;
        Vec3 getUpVector() const;
};
}

#endif // TRANSFORMCOMPONENT_H
