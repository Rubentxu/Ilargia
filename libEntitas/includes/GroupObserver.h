#ifndef GROUPOBSERVER
#define GROUPOBSERVER

#include "Group.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>


class GroupChanged;
class IComponent;

namespace Entitas {
    class Entity;
    class Group;

    enum class GroupEventType : unsigned char {
        OnEntityAdded,
        OnEntityRemoved,
        OnEntityAddedOrRemoved
    };

    class GroupObserver : public std::enable_shared_from_this<GroupObserver> {
        const std::unordered_set<Entity> _collectedEntities;
        std::vector<Group> const _groups;
        std::vector<GroupEventType> const _eventTypes;
        Group::GroupChanged _addEntityCache;

        void addEntity(const std::shared_ptr<Group> &group, const std::shared_ptr<Entity> &entity, int index,
                       const std::shared_ptr<IComponent> &component);

    public:
        std::unordered_set<Entity> GetcollectedEntities() const;

        GroupObserver(const std::shared_ptr<Group> &group, GroupEventType eventType);

        GroupObserver(std::vector<Group> &groups, std::vector<GroupEventType> &eventTypes);

        void Activate();

        void Deactivate();

        void ClearCollectedEntities();

    };

    class GroupObserverException : public std::exception {
    public:
        GroupObserverException(const std::string &message);

    protected:
        std::shared_ptr<GroupObserverException> shared_from_this() {
            return std::static_pointer_cast<GroupObserverException>(shared_from_this());
        }
    };
}


#endif	//#ifndef GROUPOBSERVER
