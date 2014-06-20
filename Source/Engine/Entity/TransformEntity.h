#ifndef TRANSFORMENTITY_H
#define TRANSFORMENTITY_H
#include <Engine/Entity/Entity.h>

struct TransformComponent
{
    Vec3        pos;
    Quaternion  rot;

    void rotate(const Vec3& axis, float angle);
    void translate(const Vec3& translation);

    Vec3 forward() const;
    Vec3 right() const;
    Vec3 up() const;
};

class TransformEntity : public Entity
{
    public:
        TransformComponent transform;
        TransformEntity(const String& name = "");
};

#endif // TRANSFORMENTITY_H
