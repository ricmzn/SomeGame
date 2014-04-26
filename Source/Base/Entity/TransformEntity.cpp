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
    return Vec3(0, 0, -1) * rot;
}

Vec3 TransformEntity::right() const
{
    return Vec3(1, 0, 0) * -rot;
}

Vec3 TransformEntity::up() const
{
    return Vec3(0, 1, 0) * rot;
}
