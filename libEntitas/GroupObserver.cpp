#include <set>
#include "GroupObserver.h"


namespace Entitas {

	std::unordered_set<Entity> GroupObserver::GetcollectedEntities() const {
		return _collectedEntities;
	}

	GroupObserver::GroupObserver(const std::shared_ptr<Group> &group, GroupEventType eventType) : GroupObserver() {
	}

	GroupObserver::GroupObserver(std::vector<Group> &groups, std::vector<GroupEventType> &eventTypes) : _collectedEntities(std::unordered_set<Entity>(EntityEqualityComparer::comparer)), _groups(groups), _eventTypes(eventTypes) {
		if(groups.size() != eventTypes.size())
			throw GroupObserverException(std::string(_TEXT("Unbalanced count with groups (")) + groups.size() + std::string(_TEXT(") and event types (")) + eventTypes.size() + std::string(_TEXT(")")));

		_addEntityCache = [&] (Entitas::Group group, Entity entity, int index, IComponent component) {addEntity(group, entity, index, component);};
		Activate();
	}

	void GroupObserver::Activate() {
		for(int i = 0, groupsLength = _groups.size(); i < groupsLength; i++) {
			auto group = _groups[i];
			auto eventType = _eventTypes[i];
			if(eventType == GroupEventType::OnEntityAdded) {
				group->OnEntityAdded->removeListener(_TEXT("_addEntityCache"));
				group->OnEntityAdded->addListener(_TEXT("_addEntityCache"), _addEntityCache);
			} else if(eventType == GroupEventType::OnEntityRemoved) {
				group->OnEntityRemoved->removeListener(_TEXT("_addEntityCache"));
				group->OnEntityRemoved->addListener(_TEXT("_addEntityCache"), _addEntityCache);
			} else if(eventType == GroupEventType::OnEntityAddedOrRemoved) {
				group->OnEntityAdded->removeListener(_TEXT("_addEntityCache"));
				group->OnEntityAdded->addListener(_TEXT("_addEntityCache"), _addEntityCache);
				group->OnEntityRemoved->removeListener(_TEXT("_addEntityCache"));
				group->OnEntityRemoved->addListener(_TEXT("_addEntityCache"), _addEntityCache);
			}
		}
	}

	void GroupObserver::Deactivate() {
		for(int i = 0, groupsLength = _groups.size(); i < groupsLength; i++) {
			auto group = _groups[i];
			group->OnEntityAdded->removeListener(_TEXT("_addEntityCache"));
			group->OnEntityRemoved->removeListener(_TEXT("_addEntityCache"));
		}
		ClearCollectedEntities();
	}

	void GroupObserver::ClearCollectedEntities() {
		for(auto entity : _collectedEntities)
			entity->Release(shared_from_this());
		_collectedEntities.clear();
	}

	void GroupObserver::addEntity(const std::shared_ptr<Group> &group, const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component) {
		auto added = _collectedEntities.insert(entity);
		if(added)
			entity->Retain(shared_from_this());
	}

	GroupObserverException::GroupObserverException(const std::string &message) : Exception(message) {
	}
}
