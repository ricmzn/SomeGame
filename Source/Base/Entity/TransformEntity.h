#ifndef TRANSFORMENTITY_H
#define TRANSFORMENTITY_H
#include <Base/Entity/Entity.h>

class TransformEntity : public Entity
{
    public:
        virtual ~TransformEntity() = 0;

        Vec3        pos;
        Quaternion  rot;

        void rotate(Vec3 axis, float angle);
        void translate(Vec3 translation);

        Vec3 forward() const;
        Vec3 right() const;
        Vec3 up() const;
};

#endif // TRANSFORMENTITY_H
