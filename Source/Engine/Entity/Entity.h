#ifndef ENTITY_H
#define ENTITY_H
#include <Engine/Base/SharedTypes.h>

class Entity
{
    public:
        typedef Array<Entity*> EntList;
        typedef int SpawnFlags;

    private:
        Tick thinkRate;
        Tick nextThink;
        Entity* parent;
        EntList children;

    protected:
        void removeChild(Entity* child);

    public:
        Entity();
        virtual ~Entity();
        virtual void spawn() = 0;
        virtual void think() = 0;

        const Entity* getParent() const;
        const EntList& getChildren() const;
        void addChild(Entity* child);
        void updateChildren();
        void setThinkRate(Tick ticks);
        Tick getThinkRate() const;
        Tick getNextThink() const;
};

#endif // ENTITY_H
