#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
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

class SpaceObject : public Entity
{
    private:
        SpaceObjectProperties props;
        Vec3 relativePosition;
    public:
        SpaceObject(const Vec3& pos);
        virtual ~SpaceObject() {}
        virtual void spawn() {}
        virtual void think() {}
        Vec3 gravityVector(const Vec3& relativePos) const;
        Vec3 parentRelativePosition() const;
        const SpaceObjectProperties& getProperties() const;
};

#endif // SPACEOBJECT_H
