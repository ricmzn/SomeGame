#ifndef ENTITY_H
#define ENTITY_H
#include <Base/SharedTypes.h>

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
        virtual void spawn(SpawnFlags flags)    = 0;
        virtual void think(float deltaTime)     = 0;

        const Entity* getParent() const;
        const EntList& getChildren() const;
        void update(float delta);
        void addChild(Entity* child);
        void setThinkRate(Tick ticks);
        Tick getThinkRate() const;
        Tick getNextThink() const;
};

#endif // ENTITY_H
