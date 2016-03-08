#include "Entity.h"

namespace Entitas {


    const int &Entity::getCreationIndex() const {
        return _creationIndex;
    }

    Entity &Entity::addComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot add component!";

        if (hasComponent(index)) {
            throw "Entity already has Component";
        }
        if(_components[index]) {
            _components[index].reset(&component);
        } else {
            _components[index] = std::unique_ptr<IComponent>(&component);
        }

        _componentIndicesCache.clear();

        if (OnComponentAdded) {
            for (auto listener : OnComponentAdded->listeners())
                listener(*this, index, _components[index]);
        }
        return *this;
    }

    Entity &Entity::removeComponent(int index) {
        if (!_isEnabled)
            throw "Cannot remove component!";

        if (!hasComponent(index)) {
            throw "Entity does not have component";
        }
        std::unique_ptr<IComponent> previousComponent;
        if (_components[index]) {
            previousComponent.reset(_components[index].release());
        }
        _componentIndicesCache.clear();
        if (OnComponentRemoved) {
            for (auto listener : OnComponentRemoved->listeners()) {
                listener(*this, index, previousComponent);
            }
        }
    }

    Entity &Entity::replaceComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot replace component!";

        if (_components[index]) {
            std::unique_ptr<IComponent> previousComponent(_components[index].release());
            _components[index].reset(&component);
            if (OnComponentReplaced) {
                for (auto listener : OnComponentReplaced->listeners())
                    listener(*this, index, previousComponent, _components[index]);
            }
            _componentIndicesCache.clear();
        } else if (&component != nullptr)
            addComponent(index, std::move(component));
        return *this;
    }


    std::vector<int>& Entity::getComponentIndices() {
        if (_componentIndicesCache.empty()) {
            for (int index = 0, componentsLength = _components.size(); index < componentsLength; index++) {
                if (_components[index])
                    _componentIndicesCache.push_back(index);
            }
        }
        return _componentIndicesCache;
    }

    bool Entity::hasComponent(int index) {
        return _components[index]? true: false;
    }

    bool Entity::hasComponents(std::vector<int> &indices) {
        for (int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
            if (!_components[indices[i]] || !_components[indices[i]].get())
                return false;
        }
        return true;
    }

    bool Entity::hasAnyComponent(std::vector<int> &indices) {
        for (int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
            if (_components[indices[i]] && _components[indices[i]].get())
                return true;
        }
        return false;
    }

    void Entity::removeAllComponents() {
        for (int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
            if (_components[i] && !_components[i].get())
                replaceComponent(i, IComponent{});
        }
    }

    void Entity::destroy() {
        removeAllComponents();
        OnComponentAdded.reset();
        OnComponentReplaced.reset();
        OnComponentRemoved.reset();
        componentNames.clear();
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
