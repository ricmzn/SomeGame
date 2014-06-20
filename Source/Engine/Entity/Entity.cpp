#include "Entity.h"
#include <Engine/Entity/RootEntity.h>

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

Entity::Entity(const String& name)
    : thinkRate(0),
      nextThink(0),
      parent(nullptr),
      root(nullptr),
      classname(name)
{}

Entity::~Entity()
{
    if (root and !classname.empty())
    {
        root->removeFromTable(this);
    }
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

void Entity::updateChildren(const Camera* camera)
{
    for (auto ent : children)
    {
        ent->updateChildren(camera);
    }
    this->think();
}

void Entity::addChild(Entity* child)
{
    const char* name = this->getName().c_str();
    const char* ch = child->getName().c_str();
    if(child->parent == nullptr)
    {
        child->spawn();
    }
    child->parent = this;

    auto pRoot = dynamic_cast<RootEntity*>(this);
    if (pRoot)
    {
        child->root = pRoot;
    }
    else
    {
        child->root = this->root;
    }
    if (!child->getName().empty())
    {
        child->root->insertOnTable(child);
    }

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

RootEntity* Entity::getRoot() const
{
    return root;
}

const String& Entity::getName() const
{
    return classname;
}
