#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <Engine/Entity/TransformEntity.h>
#include <Engine/Entity/Camera.h>

enum class FlightMode
{
    LANDED,
    SPACE,
    ATMO,
    INERTIAL
};

class PlayerController : public TransformEntity
{       
    private:
        Camera* camera;
        FlightMode mode;
        Vec3 velocity;
        Vec3 angvel;
        float drag;
    public:
        PlayerController();
        virtual void spawn(SpawnFlags flags);
        virtual void think(float deltaTime);
        void setFlightMode(FlightMode newMode);
};

#endif // PLAYERCONTROLLER_H
