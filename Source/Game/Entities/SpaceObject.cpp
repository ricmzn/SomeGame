#include "SpaceObject.h"

SpaceObject::SpaceObject(const Vec3& pos, const SpaceObjectProperties& props)
    : relativePosition(pos),
      props(props)
{}

SpaceObject::~SpaceObject()
{}

void SpaceObject::spawn()
{}

void SpaceObject::think()
{}

Vec3 SpaceObject::gravityVector(const Vec3 &relativePos) const
{
    return -VEC3_UP;
}

Vec3 SpaceObject::parentRelativePosition() const
{
    return relativePosition;
}

const SpaceObjectProperties& SpaceObject::getProperties() const
{
    return props;
}
