#include "TransformEntity.h"

void TransformComponent::translate(const Vec3& translation)
{
    pos += translation;
}

void TransformComponent::rotate(const Vec3& axis, float angle)
{
    rot = glm::rotate(rot, angle, axis);
}

Vec3 TransformComponent::forward() const
{
    return VEC3_FORWARD * rot;
}

Vec3 TransformComponent::right() const
{
    return VEC3_RIGHT * rot;
}

Vec3 TransformComponent::up() const
{
    return VEC3_UP * rot;
}

TransformEntity::TransformEntity(const String &name)
    : Entity(name)
{}
