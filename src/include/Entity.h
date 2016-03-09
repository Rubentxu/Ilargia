#ifndef ENTITAS_ENTITY_H
#define ENTITAS_ENTITY_H


#include <string>
#include <stdexcept>
#include <memory>
#include <boost/any.hpp>
#include <type_traits>
#include "Event.h"
#include "Config.h"
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace Entitas {

    struct IComponent {
        bool _isEnabled = false;

        operator bool() const {
            return _isEnabled;
        }
    };

    class Entity {
        std::unordered_map<std::type_index,std::unique_ptr<IComponent>> _components;
        std::vector<std::type_index> _componentIndicesCache;


    public:
//        std::unordered_set<boost::any> owners;
        int _creationIndex = 0;
        bool _isEnabled = true;

        using EntityChanged = std::function<void(const Entity &entity, const IComponent &component)>;
        using ComponentReplaced = std::function<void(const Entity &entity,const IComponent& previousComponent,const IComponent& newComponent)>;
        using EntityReleased = std::function<void(const Entity &entity)>;

        std::unique_ptr<Event<EntityReleased>> OnEntityReleased;
        std::unique_ptr<Event<EntityChanged>> OnComponentAdded;
        std::unique_ptr<Event<EntityChanged>> OnComponentRemoved;
        std::unique_ptr<Event<ComponentReplaced>> OnComponentReplaced;


        const int &getCreationIndex() const;

        Entity(){
            //_components.fill(std::unique_ptr<IComponent>());
        }

        template <class Derived>
        Entity& addComponent(Derived &&component) {
            static_assert(std::is_base_of<IComponent, Derived>::value,"Failed: Not derived IComponent class!");
            if (!_isEnabled)
                throw "Cannot add component!";
            auto key = std::type_index(typeid(component));
            auto it = _components.find(key);
            if (it == _components.end()) {
                auto componentAdded = _components.insert(it, std::make_pair(key, std::unique_ptr<Derived>(&component)));
                if (OnComponentAdded) {
                    for (auto listener : OnComponentAdded->listeners())
                        listener(*this, *componentAdded->second);
                }
                _componentIndicesCache.clear();
            }
            return *this;
        }

        template <typename Derived>
        Entity& removeComponent();

        template <typename Derived>
        Entity& replaceComponent(Derived &&component);

        template<typename Derived>
        Derived& getComponent() {
            auto it = _components.find(std::type_index(typeid(Derived)));
            if (it != _components.end()) {
                return static_cast<Derived&>(*it->second);
            }
            return  *(new Derived{});
        }

        std::unordered_map<std::type_index,std::unique_ptr<IComponent>>& getComponents(){
            return _components;
        }

        std::vector<std::type_index>& getComponentIndices();

        template <typename Derived>
        bool hasComponent(){
            return _components.find(std::type_index(typeid(Derived))) != _components.end();
        }

        bool hasComponents(std::vector<std::type_index>& indices);

        bool hasAnyComponent(std::vector<std::type_index> &indices);

        void removeAllComponents();

        void destroy();

        int getRetainCount() const;

        //Entity& retain(const std::shared_ptr<void> &owner);

        //void release(const std::shared_ptr<void> &owner);
    };



/*    class EntityEqualityComparer : public IEqualityComparer<Entity> {

    public:
        static const std::shared_ptr<EntityEqualityComparer> comparer;

        bool Equals(const Entity& &x, const Entity& &y);

        int GetHashCode(const Entity& &obj);
    };*/


}


#endif //ENTITAS_ENTITY_H
