#ifndef ENTITY_H
#define ENTITY_H
#include <Engine/Components/BaseComponent.h>

namespace Base {
class api_public Entity final
{
    static EntityID lastID;

    private:
        EntityID ID;
        Entity* parent;
        Array<Components::BaseComponent*> components;
    public:
        Entity(Entity* parent = nullptr);
        ~Entity();

        EntityID getID() const;
        Entity* getParent() const;

        template<typename T, typename... Args> T* newComponent(Args&&... args);
        template<typename T> bool removeComponent();
        template<typename T> T* getComponent();
};
// Template definitions
#include "Entity.inl"
}

#endif // ENTITY_H
