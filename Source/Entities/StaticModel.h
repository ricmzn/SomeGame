#ifndef STATICMODEL_H
#define STATICMODEL_H
#include <Base/Entity/MeshEntity.h>

class StaticModel : public MeshEntity
{
    public:
        StaticModel(const char* filename, Vec3 pos);
        virtual void spawn(SpawnFlags flags);
        virtual void think(float deltaTime);
};

#endif // STATICMODEL_H
