#pragma once

#include "Component.hpp"
#include "math.hpp"
#include "utils.hpp"

template <typename T>
concept IsComponent = std::is_base_of<Component, T>::value;

// TODO: Memory management of components

class GameObject
{
  public:
    Vector3<> position;

    /**
     * Returns a pointer to the component or nullptr if the component doesn't exist
     */
    template <typename T>
        requires IsComponent<T>
    T* getComponent()
    {
        for (Component *component : components)
        {
            // TODO: Check if static_cast can be used (probably not)
            T* castComponent = dynamic_cast<T *>(component);
            if (castComponent != nullptr)
            {
                return castComponent;
            }
        }
        return nullptr;
//        throw std::runtime_error("Component " + string{typeid(T).name()} + " does not exist on " + string{typeid(this).name()});
    }

    inline void addComponent(Component *component)
    {
        components.push_back(component);
    }

    template <typename T>
    bool hasComponent() requires IsComponent<T>
    {
        for (Component *component : components)
        {
            if (dynamic_cast<T *>(component) != nullptr)
            {
                return true;
            }
        }
        return false;
    }

  private:
    vector<Component *> components;
};
