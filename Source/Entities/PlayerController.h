#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <Base/Entity/TransformEntity.h>
#include <Entities/Camera.h>

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
        FlightMode mode;
        InputArray* keys;
        Vec3 velocity;
        Vec3 angvel;
        float drag;
    public:
        PlayerController(InputArray* keyArrayPtr);
        virtual ~PlayerController();
        virtual void spawn(SpawnFlags flags);
        virtual void think(float deltaTime);
        void setFlightMode(FlightMode newMode) {this->mode = newMode;}
};

#endif // PLAYERCONTROLLER_H
