#ifndef TRANSFORMENTITY_H
#define TRANSFORMENTITY_H
#include <Base/Entity/Entity.h>

class TransformEntity : public Entity
{
    public:
        struct TransformComponent
        {
            Vec3        pos;
            Quaternion  rot;

            void rotate(const Vec3& axis, float angle);
            void translate(const Vec3& translation);

            Vec3 forward() const;
            Vec3 right() const;
            Vec3 up() const;
        } transform;
};

#endif // TRANSFORMENTITY_H
