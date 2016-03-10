#include "Entity.h"

namespace Entitas {


    const int &Entity::getCreationIndex() const {
        return _creationIndex;
    }

    template <typename Derived>
    Entity &Entity::replaceComponent(Derived &&component) {
        static_assert(std::is_base_of<IComponent, Derived>::value,"Failed: Not derived IComponent class!");
        if (!_isEnabled)
            throw "Cannot replace component!";

        auto it = _components.find(typeid(component));
        if (it != _components.end()) {
            std::unique_ptr<IComponent> previousComponent(it->second.release());
            it->second.reset(&component);
            if (OnComponentReplaced) {
                for (auto listener : OnComponentReplaced->listeners())
                    listener(*this, *previousComponent, *it->second);
            }
            _componentIndicesCache.clear();
        }
        return *this;
    }

    std::vector<std::type_index>& Entity::getComponentIndices() {
        if (_componentIndicesCache.empty()) {
            for (auto &itc : _components) {
                 _componentIndicesCache.push_back(itc.first);
            }
        }
        return _componentIndicesCache;
    }


    bool Entity::hasComponents(std::vector<std::type_index>& indices) {
        for (auto it : indices) {
            if (_components.find(it) == _components.end())
                return false;
        }
        return true;
    }

    bool Entity::hasAnyComponent(std::vector<std::type_index> &indices) {
        for (auto it : indices) {
            if (_components.find(it) != _components.end())
                return true;
        }
        return false;
    }

    void Entity::removeAllComponents() {
        _components.clear();
    }

    void Entity::destroy() {
        removeAllComponents();
        OnComponentAdded.reset();
        OnComponentReplaced.reset();
        OnComponentRemoved.reset();
        _isEnabled = false;
    }

    /*int Entity::getRetainCount() const {
        return owners.size();
    }

    Entity& Entity::retain(const std::shared_ptr<void> &owner) {
        if (!owners.insert(owner).second)
            throw "Entity is already retained by owner";

        return shared_from_this();
    }

    void Entity::release(const std::shared_ptr<void> &owner) {
        owners.erase(owner);

        if (owners.empty()) {
            if (OnEntityReleased != nullptr) {
                for (auto listener : OnEntityReleased->listeners())
                    listener(this);
            }
        }
    }*/
}
