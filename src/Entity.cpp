#include "Entity.h"


namespace Entitas {

    const int &Entity::getCreationIndex() const {
        return _creationIndex;
    }

    Entity::Entity(int totalComponents) : _components(std::vector<std::unique_ptr<IComponent>>(totalComponents)) { }

    std::shared_ptr<Entity> Entity::addComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot add component!";

        if (HasComponent(index)) {
            throw "Entity already has Component";
        }

        _components[index] = std::unique_ptr<IComponent>(&component);
        _componentIndicesCache.clear();

        if (OnComponentAdded != nullptr) {
            for (auto listener : OnComponentAdded->listeners())
                listener(*this, index, component);
        }
        return shared_from_this();
    }

    std::shared_ptr<Entity> Entity::removeComponent(int index) {
        if (!_isEnabled)
            throw "Cannot remove component!";

        if (!HasComponent(index)) {
            throw "Entity does not have component";
        }
        replaceComponent(index, nullptr);
        return shared_from_this();
    }

    std::shared_ptr<Entity> Entity::replaceComponent(int index, IComponent &&component) {
        if (!_isEnabled)
            throw "Cannot replace component!";

        if (HasComponent(index))
            _replaceComponent(index, std::move(component));
        else if (&component != nullptr)
            addComponent(index, std::move(component));
        return shared_from_this();
    }

    void Entity::_replaceComponent(int index, IComponent &&replacement) {
        auto previousComponent = _components[index];
        if (previousComponent.get() == &replacement) {
            if (OnComponentReplaced != nullptr) {
                for (auto listener : OnComponentReplaced->listeners())
                    listener(this, index, previousComponent, replacement);
            }
        } else {
            _components[index].reset(&replacement);
            if (&replacement == nullptr) {
                _componentIndicesCache.clear();
                if (OnComponentRemoved != nullptr) {
                    for (auto listener : OnComponentRemoved->listeners())
                        listener(this, index, previousComponent);
                }
            } else {
                if (OnComponentReplaced != nullptr) {
                    for (auto listener : OnComponentReplaced->listeners())
                        listener(this, index, previousComponent, replacement);
                }
            }
        }
    }

    IComponent& Entity::getComponent(int index) {
        if (!HasComponent(index)) {
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

    bool Entity::HasComponent(int index) {
        return _components[index].get() != nullptr;
    }

    bool Entity::hasComponents(std::vector<int> &indices) {
        for (int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
            if (_components[indices[i]].get() == nullptr)
                return false;
        }
        return true;
    }

    bool Entity::hasAnyComponent(std::vector<int> &indices) {
        for (int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
            if (_components[indices[i]].get()
                != nullptr)
                return true;
        }
        return false;
    }

    void Entity::removeAllComponents() {
        for (int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
            if (_components[i] != nullptr)
                replaceComponent(i, nullptr);
        }
    }

    void Entity::destroy() {
        removeAllComponents();
        OnComponentAdded->addListener("nullptr", nullptr);
        OnComponentReplaced->addListener("nullptr", nullptr);
        OnComponentRemoved->addListener("nullptr", nullptr);
        componentNames.clear();
        _isEnabled = false;
    }

    /*int Entity::getRetainCount() const {
        return owners.size();
    }

    std::shared_ptr<Entity> Entity::retain(const std::shared_ptr<void> &owner) {
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
