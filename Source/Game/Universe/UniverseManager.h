#ifndef UNIVERSEMANAGER_H
#define UNIVERSEMANAGER_H
#include <Engine/Entity/Entity.h>
#include <Game/Entities/PlayerController.h>
#include <Game/Entities/SpaceObject.h>

class UniverseManager : public Entity
{
    private:
        Array<SpaceObject*> stars;
        const Vec3& reference;
    public:
        UniverseManager(const PlayerController& player) : reference(player.transform.pos) {}
        virtual ~UniverseManager();
        virtual void spawn();
        virtual void update();
        const Array<SpaceObject*>& getStars() const;
};

#endif // UNIVERSEMANAGER_H
