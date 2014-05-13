#include "TransformEntity.h"

void TransformEntity::TransformComponent::translate(const Vec3& translation)
{
    pos += translation;
}

void TransformEntity::TransformComponent::rotate(const Vec3& axis, float angle)
{
    rot = glm::rotate(rot, angle, axis);
}

Vec3 TransformEntity::TransformComponent::forward() const
{
    return VEC3_FORWARD * rot;
}

Vec3 TransformEntity::TransformComponent::right() const
{
    return VEC3_RIGHT * rot;
}

Vec3 TransformEntity::TransformComponent::up() const
{
    return VEC3_UP * rot;
}
