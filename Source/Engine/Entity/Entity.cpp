#include "Entity.h"

void Entity::removeChild(Entity* child)
{
    int index = 0;
    for (auto ent : children)
    {
        if (ent == child)
        {
            children.erase(children.begin() + index);
            break;
        }
        index++;
    }
}

Entity::Entity()
    : thinkRate(0),
      nextThink(0),
      parent(nullptr)
{}

Entity::~Entity()
{
    if (parent)
    {
        parent->removeChild(this);
    }
    for (auto ent : children)
    {
        delete ent;
    }
}

const Entity* Entity::getParent() const
{
    return parent;
}

const Entity::EntList& Entity::getChildren() const
{
    return children;
}

void Entity::update(float delta)
{
    for (auto ent : children)
    {
        ent->update(delta);
    }
    this->think(delta);
}

void Entity::addChild(Entity* child)
{
    child->parent = this;
    children.push_back(child);
}

void Entity::setThinkRate(Tick ticks)
{
    thinkRate = ticks;
}

Tick Entity::getThinkRate() const
{
    return thinkRate;
}

Tick Entity::getNextThink() const
{
    return nextThink;
}
