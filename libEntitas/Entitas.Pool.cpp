#include "Entitas.Pool.h"
#include "Group.h"
#include "Pool.h"
#include "T.h"
#include "EntityChanged.h"
#include "ComponentReplaced.h"
#include "EntityReleased.h"
#include "IMatcher.h"
#include "IComponent.h"
#include "GroupChanged.h"


namespace Entitas {

	const int &Pool::GettotalComponents() const {
		return _totalComponents;
	}

	const int &Pool::Getcount() const {
		return _entities.size();
	}

	const int &Pool::GetreusableEntitiesCount() const {
		return _reusableEntities.size();
	}

	const int &Pool::GetretainedEntitiesCount() const {
		return _retainedEntities.size();
	}

	Pool::Pool(int totalComponents) : Pool() {
	}

	Pool::Pool(int totalComponents, int startCreationIndex) : _groupsForIndex(std::vector<std::vector<Group> >(totalComponents)), _totalComponents(totalComponents) {
		_creationIndex = startCreationIndex;

		// Cache delegates to avoid gc allocations
		_cachedUpdateGroupsComponentAddedOrRemoved = [&] (Entitas::Entity entity, int index, IComponent component) {updateGroupsComponentAddedOrRemoved(entity, index, component);};
		_cachedUpdateGroupsComponentReplaced = [&] (Entitas::Entity entity, int index, IComponent previousComponent, IComponent newComponent) {updateGroupsComponentReplaced(entity, index, previousComponent, newComponent);};
		_cachedOnEntityReleased = [&] (Entitas::Entity entity) {onEntityReleased(entity);};
	}

	std::shared_ptr<Entity> Pool::CreateEntity() {
		auto entity = _reusableEntities.size() > 0 ? _reusableEntities.pop() : std::make_shared<Entity>(_totalComponents);
		entity._isEnabled = true;
		entity._creationIndex = _creationIndex++;
		entity.Retain(shared_from_this());
		_entities.insert(entity);
		_entitiesCache.clear();
		entity.OnComponentAdded += _cachedUpdateGroupsComponentAddedOrRemoved;
		entity.OnComponentRemoved += _cachedUpdateGroupsComponentAddedOrRemoved;
		entity.OnComponentReplaced += _cachedUpdateGroupsComponentReplaced;
		entity.OnEntityReleased += _cachedOnEntityReleased;

		if(OnEntityCreated != nullptr) {
			for(auto listener : OnEntityCreated->listeners())
				listener(this, entity);
		}

		return entity;
	}

	void Pool::DestroyEntity(const std::shared_ptr<Entity> &entity) {
		auto removed = _entities.Remove(entity);
		if(!removed)
			throw PoolDoesNotContainEntityException(entity, _TEXT("Could not destroy entity!"));
		_entitiesCache.clear();

		if(OnEntityWillBeDestroyed != nullptr) {
			for(auto listener : OnEntityWillBeDestroyed->listeners())
				listener(this, entity);
		}

		entity->destroy();

		if(OnEntityDestroyed != nullptr) {
			for(auto listener : OnEntityDestroyed->listeners())
				listener(this, entity);
		}

		if(entity->GetretainCount() == 1) {
			entity->OnEntityReleased->removeListener(_TEXT("_cachedOnEntityReleased"));
			_reusableEntities.push(entity);
		} else {
			_retainedEntities.insert(entity);
		}
		entity->Release(shared_from_this());
	}

	void Pool::DestroyAllEntities() {
		auto entities = GetEntities();
		for(int i = 0, entitiesLength = entities.Length; i < entitiesLength; i++)
			DestroyEntity(entities[i]);

		_entities.clear();

		if(_retainedEntities.size() != 0)
			throw PoolStillHasRetainedEntitiesException();
	}

	bool Pool::HasEntity(const std::shared_ptr<Entity> &entity) {
		return std::find(_entities.begin(), _entities.end(), entity) != _entities.end();
	}

	std::vector<Entity> Pool::GetEntities() {
		if(_entitiesCache.empty()) {
			_entitiesCache = std::vector<Entity>(_entities.size());
			_entities.CopyTo(_entitiesCache);
		}

		return _entitiesCache;
	}

	std::shared_ptr<Group> Pool::GetGroup(const std::shared_ptr<IMatcher> &matcher) {
		std::shared_ptr<Group> group;
		if(!_groups.TryGetValue(matcher, group)) {
			group = std::make_shared<Group>(matcher);
			auto entities = GetEntities();
			for(int i = 0, entitiesLength = entities.Length; i < entitiesLength; i++)
				group->HandleEntitySilently(entities[i]);
			_groups.insert(std::make_pair(matcher, group));

			for(int i = 0, indicesLength = matcher->indices->Length; i < indicesLength; i++) {
				auto index = matcher->indices[i];
				if(_groupsForIndex[index].empty())
					_groupsForIndex[index] = std::vector<Group>();
				_groupsForIndex[index].push_back(group);
			}

			if(OnGroupCreated != nullptr) {
				for(auto listener : OnGroupCreated->listeners())
					listener(this, group);
			}
		}

		return group;
	}

	void Pool::ClearGroups() {
		for(auto group : _groups) {
			group->second.RemoveAllEventHandlers();
			for(int i = 0, n = group->GetEntities()->Length; i < n; i++)
				group->second.GetEntities()[i].Release(group->second);

			if(OnGroupCleared != nullptr) {
				for(auto listener : OnGroupCleared->listeners())
					listener(this, group);
			}
		}
		_groups.clear();

		for(int i = 0, groupsForIndexLength = _groupsForIndex.size(); i < groupsForIndexLength; i++)
			_groupsForIndex[i].clear();
	}

	void Pool::ResetCreationIndex() {
		_creationIndex = 0;
	}

	void Pool::updateGroupsComponentAddedOrRemoved(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component) {
		auto groups = _groupsForIndex[index];
		if(groups.size() > 0) {
			auto events = std::vector<Group::GroupChanged>(groups.size());
			for(int i = 0, groupsCount = groups.size(); i < groupsCount; i++)
				events.push_back(groups[i].handleEntity(entity));
			for(int i = 0, eventsCount = events.size(); i < eventsCount; i++) {
				auto groupChangedEvent = events[i];
				if(groupChangedEvent != nullptr)
					groupChangedEvent(groups[i], entity, index, component);
			}
		}
	}

	void Pool::updateGroupsComponentReplaced(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &previousComponent, const std::shared_ptr<IComponent> &newComponent) {
		auto groups = _groupsForIndex[index];
		if(groups.size() > 0) {
			for(int i = 0, groupsCount = groups.size(); i < groupsCount; i++)
				groups[i].UpdateEntity(entity, index, previousComponent, newComponent);
		}
	}

	void Pool::onEntityReleased(const std::shared_ptr<Entity> &entity) {
		if(entity->_isEnabled)
			throw EntityIsNotDestroyedException(_TEXT("Cannot release entity."));
		entity->OnEntityReleased->removeListener(_TEXT("_cachedOnEntityReleased"));
		_retainedEntities.Remove(entity);
		_reusableEntities.push(entity);
	}
}
