#ifndef ROOTENTITY_H
#define ROOTENTITY_H
#include <Engine/Entity/Entity.h>
#include <Engine/Base/SharedTypes.h>

// Behold, the father of all entities!
class RootEntity final : public Entity
{
    private:
        HashTable<String, Entity*> entityTable;
        bool isAlive;

        void insertOnTable(Entity* ent);
        void removeFromTable(Entity* ent);

    public:
        RootEntity();
        virtual ~RootEntity();
        virtual void spawn();
        virtual void think();

        Entity* find(const String& name);

        friend class Entity;
};

#endif // ROOTENTITY_H
