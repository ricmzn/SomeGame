#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H
#include <Engine/Entity/Entity.h>

enum class SpaceObjectType
{
    INVISIBLE,
    NEBULA,
    STAR,
    PLANET,
    MOON,
    ASTEROID,
    DEBRIS
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
        Vec3 relativePosition;
        SpaceObjectProperties props;
    public:
        SpaceObject(const Vec3& pos, const SpaceObjectProperties& props);
        virtual ~SpaceObject();
        virtual void spawn();
        virtual void think();
        Vec3 gravityVector(const Vec3& relativePos) const;
        Vec3 parentRelativePosition() const;
        const SpaceObjectProperties& getProperties() const;
};

#endif // SPACEOBJECT_H
