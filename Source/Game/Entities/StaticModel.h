#ifndef STATICMODEL_H
#define STATICMODEL_H
#include <Engine/Entity/MeshEntity.h>

class StaticModel : public MeshEntity
{
    public:
        StaticModel(const char* filename, Vec3 pos);
        virtual void spawn();
        virtual void think();
};

#endif // STATICMODEL_H
