#include "RootEntity.h"
#include <utility>
using std::make_pair;

void RootEntity::insertOnTable(Entity* ent)
{
    if (isAlive)
    {
        entityTable.insert(make_pair(ent->getName(), ent));
    }
}

void RootEntity::removeFromTable(Entity* ent)
{
    if (isAlive)
    {
        auto iter = entityTable.find(ent->getName());
        entityTable.erase(iter);
    }
}

RootEntity::RootEntity()
    : isAlive(true)
{}

RootEntity::~RootEntity()
{
    puts("RootEntity killed!");
    isAlive = false;
}

void RootEntity::spawn()
{}

void RootEntity::think()
{}

Entity* RootEntity::find(const String& name)
{
    auto iter = entityTable.find(name);
    // Return NULL if empty
    if (iter == entityTable.end()) {
        return nullptr;
    }
    return iter->second;
}
