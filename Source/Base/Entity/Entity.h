#ifndef ENTITY_H
#define ENTITY_H
#include <Base/SharedTypes.h>

class Entity
{
    public:
        typedef List<Entity*> EntList;
        typedef int SpawnFlags;

    private:
        Entity* parent;
        EntList children;
        Tick thinkRate;
        Tick nextThink;

    protected:
        void removeChild(Entity* child);

    public:
        Entity();
        virtual ~Entity();
        virtual void spawn(SpawnFlags flags)    = 0;
        virtual void think(float deltaTime)    = 0;

        const Entity* getParent() const;
        const EntList& getChildren() const;
        void update(float delta);
        void addChild(Entity* child);
        void setThinkRate(Tick ticks);
        Tick getThinkRate() const;
        Tick getNextThink() const;
};

#endif // ENTITY_H
