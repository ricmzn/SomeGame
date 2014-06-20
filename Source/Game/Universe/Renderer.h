#ifndef UNIVERSERENDERER_H
#define UNIVERSERENDERER_H
#include <Engine/Entity/DrawableEntity.h>
#include <Game/Entities/SpaceObject.h>

namespace Universe
{
    class Renderer : DrawableEntity
    {
    private:
        const Array<SpaceObject>& stars;
    public:
        Renderer(const Array<SpaceObject>& starArray);
        virtual void spawn() {}
        virtual void think() {}
        virtual void draw(const Camera* camera) {}
    };
}

#endif // UNIVERSERENDERER_H
