#ifndef ENTITY_H
#define ENTITY_H
#include <Engine/Base/SharedTypes.h>

// This workaround makes me sad :(
namespace Render {
    class Camera;
} using Render::Camera;
class RootEntity;

class Entity
{
    public:
        typedef Array<Entity*> EntList;

    private:
        Tick thinkRate;
        Tick nextThink;
        Entity* parent;
        RootEntity* root;
        EntList children;
        String classname;

    protected:
        void removeChild(Entity* child);

    public:
        Entity(const String& name = "");
        virtual ~Entity();
        virtual void spawn() = 0;
        virtual void think() = 0;
        virtual void updateChildren(const Camera* camera);

        void addChild(Entity* child);
        void setThinkRate(Tick ticks);
        const Entity* getParent() const;
        const EntList& getChildren() const;
        Tick getThinkRate() const;
        Tick getNextThink() const;
        RootEntity* getRoot() const;
        const String& getName() const;
};

#endif // ENTITY_H
