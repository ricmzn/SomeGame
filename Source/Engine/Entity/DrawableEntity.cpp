#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(const String& name)
    : TransformEntity(name)
{}

void DrawableEntity::updateChildren(const Camera* camera)
{
    Entity::updateChildren(camera);
    this->draw(camera);
}
