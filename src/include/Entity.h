#ifndef ENTITAS_ENTITY_H
#define ENTITAS_ENTITY_H


#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <unordered_set>
#include <boost/any.hpp>
#include "Event.h"
#include "bitscan.h"

namespace Entitas {

    class IComponent {
        bool _isEnabled = false;

    public:
        operator bool() const {
            return _isEnabled;
        }
    };

    class Entity : public std::enable_shared_from_this<Entity> {

        std::vector<std::unique_ptr<IComponent>> _components;
        std::vector<int> _componentIndicesCache;

        void _replaceComponent(int index, IComponent &&component);

    public:
//        std::unordered_set<boost::any> owners;
        std::vector<std::string> componentNames;
        int _creationIndex = 0;
        bool _isEnabled = true;

        using EntityChanged = std::function<void(const Entity &entity, int index, const std::unique_ptr<IComponent> &component)>;
        using ComponentReplaced = std::function<void(const Entity &entity, int index, const std::unique_ptr<IComponent> &previousComponent,
                                                     const std::unique_ptr<IComponent> &newComponent)>;

        std::unique_ptr<Event<EntityChanged>> OnComponentAdded;
        std::unique_ptr<Event<EntityChanged>> OnComponentRemoved;
        std::unique_ptr<Event<ComponentReplaced>> OnComponentReplaced;


        const int &getCreationIndex() const;

        Entity(int totalComponents);

        std::shared_ptr<Entity> addComponent(int index, IComponent &&component);

        std::shared_ptr<Entity> removeComponent(int index);

        std::shared_ptr<Entity> replaceComponent(int index, IComponent &&component);

        IComponent& getComponent(int index);

        std::vector<std::unique_ptr<IComponent>>& getComponents();

        std::vector<int>& getComponentIndices();

        bool hasComponent(int index);

        bool hasComponents(std::vector<int> &indices);

        bool hasAnyComponent(std::vector<int> &indices);

        void removeAllComponents();

        void destroy();

        using EntityReleased = std::function<void(const std::shared_ptr<Entity> &entity)>;
        std::unique_ptr<Event<EntityReleased>> OnEntityReleased;

        int getRetainCount() const;

        //std::shared_ptr<Entity> retain(const std::shared_ptr<void> &owner);

        //void release(const std::shared_ptr<void> &owner);
    };



/*    class EntityEqualityComparer : public IEqualityComparer<Entity> {

    public:
        static const std::shared_ptr<EntityEqualityComparer> comparer;

        bool Equals(const std::shared_ptr<Entity> &x, const std::shared_ptr<Entity> &y);

        int GetHashCode(const std::shared_ptr<Entity> &obj);
    };*/


}


#endif //ENTITAS_ENTITY_H
