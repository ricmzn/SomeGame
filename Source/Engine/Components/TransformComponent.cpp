#include "TransformComponent.h"
using namespace Components;

void TransformComponent::translate(const Vec3& translation)
{
    position += translation;
}

void TransformComponent::rotate(const Vec3& axis, float angle)
{
    glm::rotate(rotation, angle, axis);
}

void TransformComponent::rescale(const Base::Types::Vec3& factor)
{
    scale = scale * factor;
}

Vec3 TransformComponent::getForwardVector() const
{
    return VEC3_FORWARD * rotation;
}

Vec3 TransformComponent::getRightVector() const
{
    return VEC3_RIGHT * rotation;
}

Vec3 TransformComponent::getUpVector() const
{
    return VEC3_UP * rotation;
}
