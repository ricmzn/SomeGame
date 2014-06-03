#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H
#include <Engine/Entity/TransformEntity.h>
#include <Engine/Render/Camera.h>

class DrawableEntity : public TransformEntity
{
    public:
        virtual void draw(const Camera* camera) = 0;
};

#endif // DRAWABLEENTITY_H
