#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H
#include <Engine/Entity/TransformEntity.h>
#include <Engine/Render/Camera.h>

class DrawableEntity : public TransformEntity
{
    public:
        DrawableEntity(const String& name = "");
        virtual void draw(const Camera* camera) = 0;
        virtual void updateChildren(const Camera* camera);
};

#endif // DRAWABLEENTITY_H
