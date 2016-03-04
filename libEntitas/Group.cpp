#include "Group.h"

namespace Entitas {

	const int &Group::Getcount() const {
		return _entities.size();
	}

	const std::shared_ptr<IMatcher> &Group::Getmatcher() const {
		return _matcher;
	}

	Group::Group(const std::shared_ptr<IMatcher> &matcher) : _matcher(matcher) {
	}

	void Group::HandleEntitySilently(const std::shared_ptr<Entity> &entity) {
		if(_matcher->Matches(entity))
			addEntitySilently(entity);
		else
			removeEntitySilently(entity);
	}

	void Group::HandleEntity(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component) {
		if(_matcher->Matches(entity))
			addEntity(entity, index, component);
		else
			removeEntity(entity, index, component);
	}

	Group::GroupChanged Group::handleEntity(const std::shared_ptr<Entity> &entity) {
		return _matcher->Matches(entity) ? addEntity(entity) : removeEntity(entity);
	}

	void Group::UpdateEntity(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &previousComponent, const std::shared_ptr<IComponent> &newComponent) {
		if(std::find(_entities.begin(), _entities.end(), entity) != _entities.end()) {
			if(OnEntityRemoved != nullptr) {
				for(auto listener : OnEntityRemoved->listeners())
					listener(this, entity, index, previousComponent);
			}
			if(OnEntityAdded != nullptr) {
				for(auto listener : OnEntityAdded->listeners())
					listener(this, entity, index, newComponent);
			}
			if(OnEntityUpdated != nullptr) {
				for(auto listener : OnEntityUpdated->listeners())
					listener(this, entity, index, previousComponent, newComponent);
			}
		}
	}

	void Group::RemoveAllEventHandlers() {
		OnEntityAdded->addListener(_TEXT("nullptr"), nullptr);
		OnEntityRemoved->addListener(_TEXT("nullptr"), nullptr);
		OnEntityUpdated->addListener(_TEXT("nullptr"), nullptr);
	}

	bool Group::addEntitySilently(const std::shared_ptr<Entity> &entity) {
		auto added = _entities.insert(entity);
		if(added) {
			_entitiesCache.clear();
			_singleEntityCache.reset();
			entity->Retain(shared_from_this());
		}

		return added;
	}

	void Group::addEntity(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component) {
		if(addEntitySilently(entity) && OnEntityAdded != nullptr) {
			for(auto listener : OnEntityAdded->listeners())
				listener(this, entity, index, component);
		}
	}

	Group::GroupChanged Group::addEntity(const std::shared_ptr<Entity> &entity) {
		return addEntitySilently(entity) ? OnEntityAdded : nullptr;
	}

	bool Group::removeEntitySilently(const std::shared_ptr<Entity> &entity) {
		auto removed = _entities.Remove(entity);
		if(removed) {
			_entitiesCache.clear();
			_singleEntityCache.reset();
			entity->Release(shared_from_this());
		}

		return removed;
	}

	void Group::removeEntity(const std::shared_ptr<Entity> &entity, int index, const std::shared_ptr<IComponent> &component) {
		auto removed = _entities.Remove(entity);
		if(removed) {
			_entitiesCache.clear();
			_singleEntityCache.reset();
			if(OnEntityRemoved != nullptr) {
				for(auto listener : OnEntityRemoved->listeners())
					listener(this, entity, index, component);
			}
			entity->Release(shared_from_this());
		}
	}

	Group::GroupChanged Group::removeEntity(const std::shared_ptr<Entity> &entity) {
		return removeEntitySilently(entity) ? OnEntityRemoved : nullptr;
	}

	bool Group::ContainsEntity(const std::shared_ptr<Entity> &entity) {
		return std::find(_entities.begin(), _entities.end(), entity) != _entities.end();
	}

	std::vector<Entity> Group::GetEntities() {
		if(_entitiesCache.empty()) {
			_entitiesCache = std::vector<Entity>(_entities.size());
			_entities.CopyTo(_entitiesCache);
		}

		return _entitiesCache;
	}

	std::shared_ptr<Entity> Group::GetSingleEntity() {
		if(_singleEntityCache == nullptr) {
			auto c = _entities.size();
			if(c == 1) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var enumerator = _entities.GetEnumerator())
			{
					auto enumerator = _entities.begin();
					enumerator->MoveNext();
					_singleEntityCache = enumerator->Current;
			}
			} else if(c == 0) {
				return nullptr;
			} else {
				throw SingleEntityException(_matcher);
			}
		}

		return _singleEntityCache;
	}

	std::string Group::ToString() {
		if(_toStringCache == _TEXT(""))
			_toStringCache = std::string(_TEXT("Group(")) + _matcher + std::string(_TEXT(")"));
		return _toStringCache;
	}

	SingleEntityException::SingleEntityException(const std::shared_ptr<IMatcher> &matcher) : Exception(std::string(_TEXT("Multiple entities exist matching ")) + matcher) {
	}
}
