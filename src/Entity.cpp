#include "Entity.h"

namespace Entitas {

    Entity::Entity(int totalComponents) : _components(std::vector<std::unique_ptr<IComponent>>(totalComponents)) { }

    const int &Entity::getCreationIndex() const {
        return _creationIndex;
    }

    Entity& Entity::addComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot add component!";

        if (hasComponent(index)) {
            throw "Entity already has Component";
        }
        bitarray bbi(100);
        bbi.set_bit(10);

        _components[index] = std::unique_ptr<IComponent>(&component);
        _componentIndicesCache.clear();

        if (OnComponentAdded != nullptr) {
            for (auto listener : OnComponentAdded->listeners())
                listener(*this, index, _components[index]);
        }
        return shared_from_this();
    }

    Entity& Entity::removeComponent(int index) {
        if (!_isEnabled)
            throw "Cannot remove component!";

        if (!hasComponent(index)) {
            throw "Entity does not have component";
        }
        replaceComponent(index, IComponent{});
        return shared_from_this();
    }

    Entity& Entity::replaceComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot replace component!";

        if (hasComponent(index))
            _replaceComponent(index, std::move(component));
        else if (&component != nullptr)
            addComponent(index, std::move(component));
        return shared_from_this();
    }

    void Entity::_replaceComponent(int index, IComponent &&replacement) {
        if (_components[index]) {
            if (!_components[index].get() && !replacement) {
                return;
            }
        }
        std::unique_ptr<IComponent> previousComponent(_components[index].release());
        _components[index].reset(&replacement);
        if (!replacement) {
            _componentIndicesCache.clear();
            if (OnComponentRemoved) {
                for (auto listener : OnComponentRemoved->listeners()) {
                    listener(*this, index, previousComponent);
                }
            }
        } else {
            if (OnComponentReplaced != nullptr) {
                for (auto listener : OnComponentReplaced->listeners())
                    listener(*this, index, previousComponent, _components[index]);
            }
        }
    }

    IComponent &Entity::getComponent(int index) {
        if (!hasComponent(index)) {
            throw "Entity does not have component";
        }
        return *_components[index].get();
    }

    std::vector<std::unique_ptr<IComponent>>& Entity::getComponents() {
        return _components;
    }

    std::vector<int>& Entity::getComponentIndices() {
        if (_componentIndicesCache.empty()) {
            auto indices = std::vector<int>(16);
            for (int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
                if (_components[i] != nullptr)
                    _componentIndicesCache.push_back(i);
            }
        }
        return _componentIndicesCache;
    }

    bool Entity::hasComponent(int index) {
        return _components[index] && _components[index].get();
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
