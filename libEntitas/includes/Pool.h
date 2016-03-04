#ifndef POOL
#define POOL

#include <string>
#include <stdexcept>
#include <memory>

namespace Entitas {
    class Entity;

    class Group;

    class EntityChanged;

    class ComponentReplaced;

    class EntityReleased;

    class IMatcher;

    class IComponent;

    class GroupChanged;

    class Pool : public std::enable_shared_from_this<Pool> {
        const std::stack<Entity> _reusableEntities = std::stack<Entity>();
        const std::unordered_set<Entity> _retainedEntities = std::unordered_set<Entity>();

        const int _totalComponents;
        int _creationIndex = 0;
        std::vector<Entity> _entitiesCache;

        // Cache delegates to avoid gc allocations
        Entity::EntityChanged _cachedUpdateGroupsComponentAddedOrRemoved;
        Entity::ComponentReplaced _cachedUpdateGroupsComponentReplaced;
        Entity::EntityReleased _cachedOnEntityReleased;

    protected:
        //const std::unordered_set<Entity> _entities = std::unordered_set<Entity>(EntityEqualityComparer::comparer);

        const std::unordered_map<IMatcher, Group> _groups = std::unordered_map<IMatcher, Group>();

        std::vector<std::vector<Group> > const _groupsForIndex;

        void updateGroupsComponentAddedOrRemoved(const std::shared_ptr<Entity> &entity, int index,
                                                 const std::shared_ptr<IComponent> &component);

        void updateGroupsComponentReplaced(const std::shared_ptr<Entity> &entity, int index,
                                           const std::shared_ptr<IComponent> &previousComponent,
                                           const std::shared_ptr<IComponent> &newComponent);

        void onEntityReleased(const std::shared_ptr<Entity> &entity);

    public:
        TangibleEvent <PoolChanged> *OnEntityCreated = new TangibleEvent<PoolChanged>();
        TangibleEvent <PoolChanged> *OnEntityWillBeDestroyed = new TangibleEvent<PoolChanged>();
        TangibleEvent <PoolChanged> *OnEntityDestroyed = new TangibleEvent<PoolChanged>();
        TangibleEvent <GroupChanged> *OnGroupCreated = new TangibleEvent<GroupChanged>();
        TangibleEvent <GroupChanged> *OnGroupCleared = new TangibleEvent<GroupChanged>();

        using PoolChanged = std::function<void(const std::shared_ptr<Pool> &pool,
                                               const std::shared_ptr<Entity> &entity)>;
        using GroupChanged = std::function<void(const std::shared_ptr<Pool> &pool,
                                                const std::shared_ptr<Group> &group)>;

        const int &GettotalComponents() const;

        const int &Getcount() const;

        const int &GetreusableEntitiesCount() const;

        const int &GetretainedEntitiesCount() const;

        Pool(int totalComponents);

        Pool(int totalComponents, int startCreationIndex);

        virtual std::shared_ptr<Entity> CreateEntity();

        virtual void DestroyEntity(const std::shared_ptr<Entity> &entity);

        virtual void DestroyAllEntities();

        virtual bool HasEntity(const std::shared_ptr<Entity> &entity);

        virtual std::vector<Entity> GetEntities();

        virtual std::shared_ptr<Group> GetGroup(const std::shared_ptr<IMatcher> &matcher);

        void ClearGroups();

        void ResetCreationIndex();

    };

    class PoolDoesNotContainEntityException : public std::exception {
    public:
        PoolDoesNotContainEntityException(const std::shared_ptr<Entity> &entity, const std::string &message);

    protected:
        std::shared_ptr<PoolDoesNotContainEntityException> shared_from_this() {
            return std::static_pointer_cast<PoolDoesNotContainEntityException>(shared_from_this());
        }
    };

    class EntityIsNotDestroyedException : public std::exception {
    public:
        EntityIsNotDestroyedException(const std::string &message);

    protected:
        std::shared_ptr<EntityIsNotDestroyedException> shared_from_this() {
            return std::static_pointer_cast<EntityIsNotDestroyedException>(shared_from_this());
        }
    };

    class PoolStillHasRetainedEntitiesException : public std::exception {

    protected:
        std::shared_ptr<PoolStillHasRetainedEntitiesException> shared_from_this() {
            return std::static_pointer_cast<PoolStillHasRetainedEntitiesException>(shared_from_this());
        }
    };

    class ISetPool {
    public:
        virtual void SetPool(const std::shared_ptr<Pool> &pool) = 0;
    };

    class PoolExtension final : public std::enable_shared_from_this<PoolExtension> {
        static void setPool(const std::shared_ptr<ISystem> &system, const std::shared_ptr<Pool> &pool);
    public:
        static std::vector<Entity> GetEntities(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IMatcher> &matcher);

        template<typename T>
        static std::shared_ptr<ISystem> CreateSystem(const std::shared_ptr<Pool> &pool);

        static std::shared_ptr<ISystem> CreateSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<Type> &systemType);

        static std::shared_ptr<ISystem> CreateSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<ISystem> &system);

    };
}


#endif	//#ifndef POOL
