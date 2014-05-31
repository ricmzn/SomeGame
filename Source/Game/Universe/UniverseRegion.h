#ifndef UNIVERSEREGION_H
#define UNIVERSEREGION_H
#include <Engine/Base/SharedTypes.h>
class SpaceObject;

class UniverseRegion
{
    private:
        UniverseRegion* nodes;
        SpaceObject* stars;
    public:
        UniverseRegion();
        ~UniverseRegion();
        const SpaceObject* getStars() const;
        Array<SpaceObject> getStarsRecursive() const;
};

#endif // UNIVERSEREGION_H
