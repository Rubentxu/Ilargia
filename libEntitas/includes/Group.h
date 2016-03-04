#ifndef GROUP
#define GROUP

#include "Entity.h"
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "tangible_event.h"

class IMatcher;

class GroupChanged;

class IComponent;

namespace Entitas {
    class Entity;

    class Group : public std::enable_shared_from_this<Group> {
        const std::shared_ptr<IMatcher> _matcher;
        //const std::unordered_set<Entity> _entities = std::unordered_set<Entity>(EntityEqualityComparer::comparer);
        std::vector<Entity> _entitiesCache;
        std::shared_ptr<Entity> _singleEntityCache;
        std::string _toStringCache;
        bool addEntitySilently(const std::shared_ptr<Entity> &entity);

        void addEntity(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component);

        GroupChanged addEntity(const std::shared_ptr<Entity> &entity);

        bool removeEntitySilently(const std::shared_ptr<Entity> &entity);

        void removeEntity(const std::shared_ptr<Entity> &entity, int index,
                          const std::shared_ptr<IComponent> &component);

        GroupChanged removeEntity(const std::shared_ptr<Entity> &entity);

    public:
        TangibleEvent<GroupChanged> *OnEntityAdded = new TangibleEvent<GroupChanged>();
        TangibleEvent<GroupChanged> *OnEntityRemoved = new TangibleEvent<GroupChanged>();
        TangibleEvent<GroupUpdated> *OnEntityUpdated = new TangibleEvent<GroupUpdated>();

        using GroupChanged = std::function<void(const std::shared_ptr<Group> &group,
                                                const std::shared_ptr<Entity> &entity, int index,
                                                const std::shared_ptr<IComponent> &component)>;
        using GroupUpdated = std::function<void(const std::shared_ptr<Group> &group,
                                                const std::shared_ptr<Entity> &entity, int index,
                                                const std::shared_ptr<IComponent> &previousComponent,
                                                const std::shared_ptr<IComponent> &newComponent)>;

        const int &Getcount() const;

        const std::shared_ptr<IMatcher> &Getmatcher() const;

        Group(const std::shared_ptr<IMatcher> &matcher);

        void HandleEntitySilently(const std::shared_ptr<Entity> &entity);

        void HandleEntity(const std::shared_ptr<Entity> &entity, int index,
                          const std::shared_ptr<IComponent> &component);

        GroupChanged handleEntity(const std::shared_ptr<Entity> &entity);

        void UpdateEntity(const std::shared_ptr<Entity> &entity, int index,
                          const std::shared_ptr<IComponent> &previousComponent,
                          const std::shared_ptr<IComponent> &newComponent);

        void RemoveAllEventHandlers();

        bool ContainsEntity(const std::shared_ptr<Entity> &entity);

        std::vector<Entity> GetEntities();

        std::shared_ptr<Entity> GetSingleEntity();

        virtual std::string ToString();
    };

    class SingleEntityException : public std::exception {
    public:
        SingleEntityException(const std::shared_ptr<IMatcher> &matcher);

    protected:
        std::shared_ptr<SingleEntityException> shared_from_this() {
            return std::static_pointer_cast<SingleEntityException>(shared_from_this());
        }
    };

    class GroupExtension final : public std::enable_shared_from_this<GroupExtension> {
    public:
        static std::shared_ptr<GroupObserver> CreateObserver(const std::shared_ptr<Group> &group, const std::shared_ptr<GroupEventType> &eventType = GroupEventType::OnEntityAdded);
    };
}

#endif	//#ifndef GROUP
