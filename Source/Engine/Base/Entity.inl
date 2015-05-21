template<typename T, typename... Args>
T* Entity::newComponent(Args&&... args)
{
    static_assert(std::is_base_of<Components::BaseComponent, T>::value, "T must inherit from Component!");

    // Try to find existing component of type. If one already exists, replace it. Otherwise, create a new one.
    // This is so getComponent<T> makes sense by returning only a single pointer, if an entity ever needs multiple components of the same type, it won't work anymore. For now, a new entity needs to be instanced with the desired duplicate component if such behavior is required.
    T* ptr = getComponent<T>();
    if(ptr) {
        delete ptr;
    }
    ptr = new T(args...);
    components.push_back(ptr);
    return ptr;
}

template<typename T>
bool Entity::removeComponent()
{
    auto it = components.begin();
    while(it != components.end()) {
        auto castPointer = dynamic_cast<T*>(*it);
        if(castPointer) {
            delete castPointer;
            components.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

template<typename T>
T* Entity::getComponent()
{
    for(auto component : components) {
        auto castPointer = dynamic_cast<T*>(component);
        if(castPointer) {
            return castPointer;
        }
    }
    return nullptr;
}
