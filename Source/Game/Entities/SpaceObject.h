#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include <Game/Universe/UniverseRegion.h>
#include <Engine/Entity/Entity.h>

enum class SpaceObjectType
{
    INVISIBLE,
    NEBULA,
    RED_GIANT,
    YELLOW_STAR,
    BLUE_STAR,
    WHITE_DWARF,
    BROWN_DWARF,
    GAS_GIANT,
    PLANET,
    MOON,
    ASTEROID
};

struct SpaceObjectProperties
{
    float diameter;
    float density;
    float mass;
    float rotationPeriod;
    float orbitalPeriod;
    SpaceObjectType type;
};

class SpaceObject : Entity
{
    private:
        UniverseRegion* region;
        SpaceObjectProperties props;
        Vec3 relativePosition;
    public:
        SpaceObject();
        ~SpaceObject();
        Vec3 gravityVector(const Vec3& relativePos) const;
        Vec3 parentRelativePosition() const;
        const SpaceObjectProperties& getProperties() const;
};

#endif // SPACEOBJECT_H
