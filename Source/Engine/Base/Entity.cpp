#include "Entity.h"
using namespace Base;

EntityID Entity::lastID = 0;

Entity::Entity(Entity* parent)
    : ID(lastID++),
      parent(parent)
{}

Entity::~Entity()
{
    for(Components::BaseComponent* ptr : components) {
        delete ptr;
    }
}

EntityID Entity::getID() const
{
    return ID;
}

Entity* Entity::getParent() const
{
    return parent;
}
