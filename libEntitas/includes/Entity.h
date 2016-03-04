#ifndef ENTITY
#define ENTITY

#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
//#include <boost/any.hpp>
#include "tangible_event.h"

namespace Entitas {
    class IComponent { };

    class Entity : public std::enable_shared_from_this<Entity> {

        std::vector<IComponent> const _components;
        std::vector<IComponent> _componentsCache;
        std::vector<int> _componentIndicesCache;
        std::string _toStringCache;

        void replaceComponent(int index, const std::shared_ptr<IComponent> &replacement);

    public:
        TangibleEvent<EntityChanged> *OnComponentAdded = new TangibleEvent<EntityChanged>();
        TangibleEvent<EntityChanged> *OnComponentRemoved = new TangibleEvent<EntityChanged>();
        TangibleEvent<ComponentReplaced> *OnComponentReplaced = new TangibleEvent<ComponentReplaced>();

        using EntityChanged = std::function<void(const std::shared_ptr<Entity> &entity, int index,
                                                 const std::shared_ptr<IComponent> &component)>;
        using ComponentReplaced = std::function<void(const std::shared_ptr<Entity> &entity, int index,
                                                     const std::shared_ptr<IComponent> &previousComponent,
                                                     const std::shared_ptr<IComponent> &newComponent)>;

        std::vector<std::string> componentNames;

        const int &GetcreationIndex() const;

        int _creationIndex = 0;
        bool _isEnabled = true;

        Entity(int totalComponents);

        std::shared_ptr<Entity> AddComponent(int index, const std::shared_ptr<IComponent> &component);

        std::shared_ptr<Entity> RemoveComponent(int index);

        std::shared_ptr<Entity> ReplaceComponent(int index, const std::shared_ptr<IComponent> &component);

        std::shared_ptr<IComponent> GetComponent(int index);

        std::vector<IComponent> GetComponents();

        std::vector<int> GetComponentIndices();

        bool HasComponent(int index);

        bool HasComponents(std::vector<int> &indices);

        bool HasAnyComponent(std::vector<int> &indices);

        void RemoveAllComponents();

        void destroy();

        virtual std::string ToString();


        TangibleEvent<EntityReleased> *OnEntityReleased = new TangibleEvent<EntityReleased>();
        using EntityReleased = std::function<void(const std::shared_ptr<Entity> &entity)>;

        const int &GetretainCount() const;

        const std::unordered_set<boost::any> owners = std::unordered_set<boost::any>();

        std::shared_ptr<Entity> Retain(const std::shared_ptr<void> &owner);

        void Release(const std::shared_ptr<void> &owner);
    };

    class EntityAlreadyHasComponentException : public std::exception {
    public:
        EntityAlreadyHasComponentException(const std::string &message, int index);

    protected:
        std::shared_ptr<EntityAlreadyHasComponentException> shared_from_this() {
            return std::static_pointer_cast<EntityAlreadyHasComponentException>(shared_from_this());
        }
    };

    class EntityDoesNotHaveComponentException : public std::exception {
    public:
        EntityDoesNotHaveComponentException(const std::string &message, int index);

    protected:
        std::shared_ptr<EntityDoesNotHaveComponentException> shared_from_this() {
            return std::static_pointer_cast<EntityDoesNotHaveComponentException>(shared_from_this());
        }
    };

    class EntityIsNotEnabledException : public std::exception {
    public:
        EntityIsNotEnabledException(const std::string &message);

    protected:
        std::shared_ptr<EntityIsNotEnabledException> shared_from_this() {
            return std::static_pointer_cast<EntityIsNotEnabledException>(shared_from_this());
        }
    };

/*    class EntityEqualityComparer : public IEqualityComparer<Entity> {

    public:
        static const std::shared_ptr<EntityEqualityComparer> comparer;

        bool Equals(const std::shared_ptr<Entity> &x, const std::shared_ptr<Entity> &y);

        int GetHashCode(const std::shared_ptr<Entity> &obj);
    };*/


    class EntityIsAlreadyRetainedByOwnerException : public std::exception {
    public:
        EntityIsAlreadyRetainedByOwnerException(const std::shared_ptr<void> &owner);

    protected:
        std::shared_ptr<EntityIsAlreadyRetainedByOwnerException> shared_from_this() {
            return std::static_pointer_cast<EntityIsAlreadyRetainedByOwnerException>(shared_from_this());
        }
    };

    class EntityIsNotRetainedByOwnerException : public std::exception {
    public:
        EntityIsNotRetainedByOwnerException(const std::shared_ptr<void> &owner);

    protected:
        std::shared_ptr<EntityIsNotRetainedByOwnerException> shared_from_this() {
            return std::static_pointer_cast<EntityIsNotRetainedByOwnerException>(shared_from_this());
        }
    };

    class EntityExtension final : public std::enable_shared_from_this<EntityExtension> {
    public:
        static const std::string COMPONENT_SUFFIX;

        static std::string RemoveComponentSuffix(const std::shared_ptr<Type> &type);
    };
}


#endif	//#ifndef ENTITY
