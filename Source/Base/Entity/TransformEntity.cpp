#include "TransformEntity.h"

void TransformEntity::translate(Vec3 translation)
{
    pos += translation;
}

void TransformEntity::rotate(Vec3 axis, float angle)
{
    rot = glm::rotate(rot, angle, axis);
}

Vec3 TransformEntity::forward() const
{
    return VEC3_FORWARD * rot;
}

Vec3 TransformEntity::right() const
{
    return VEC3_RIGHT * rot;
}

Vec3 TransformEntity::up() const
{
    return VEC3_UP * rot;
}
