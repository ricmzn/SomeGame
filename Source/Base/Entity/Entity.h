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
        tick_t thinkRate;
        tick_t nextThink;

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
        void setThinkRate(tick_t ticks);
        tick_t getThinkRate() const;
        tick_t getNextThink() const;
};

#endif // ENTITY_H
