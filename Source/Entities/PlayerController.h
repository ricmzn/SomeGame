#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <Base/Entity/TransformEntity.h>
#include <Entities/Camera.h>

class PlayerController : public TransformEntity
{
    private:
        KeyArray* keys;
        Vec3 velocity;
        float drag;
    public:
        PlayerController(KeyArray* keyArrayPtr);
        virtual ~PlayerController();
        virtual void spawn(SpawnFlags flags);
        virtual void think(float deltaTime);
};

#endif // PLAYERCONTROLLER_H
