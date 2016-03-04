#include "ReactiveSystem.h"
#include "GroupObserver.h"
#include "Entitas.Entity.h"
#include "Entitas.Pool.h"
#include "Group.h"
#include "IReactiveExecuteSystem.h"
#include "IMatcher.h"
#include "IReactiveSystem.h"
#include "IMultiReactiveSystem.h"
#include "TriggerOnEvent.h"
#include "IEnsureComponents.h"
#include "IExcludeComponents.h"


namespace Entitas {

	const std::shared_ptr<IReactiveExecuteSystem> &ReactiveSystem::Getsubsystem() const {
		return _subsystem;
	}

	ReactiveSystem::ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IReactiveSystem> &subSystem) : ReactiveSystem() {
	}

	ReactiveSystem::ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IMultiReactiveSystem> &subSystem) : ReactiveSystem() {
	}

	ReactiveSystem::ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IReactiveExecuteSystem> &subSystem, std::vector<TriggerOnEvent> &triggers) : _subsystem(subSystem), _observer(std::make_shared<GroupObserver>(groups, eventTypes)), _ensureComponents(ensureComponents::ensureComponents), _excludeComponents(excludeComponents::excludeComponents), _clearAfterExecute(std::static_pointer_cast<std::dynamic_pointer_cast<IClearReactiveSystem>(subSystem)>(!) = nullptr), _buffer(std::vector<Entity>()) {
		auto ensureComponents = std::dynamic_pointer_cast<IEnsureComponents>(subSystem);
		if(ensureComponents != nullptr) {
		}
		auto excludeComponents = std::dynamic_pointer_cast<IExcludeComponents>(subSystem);
		if(excludeComponents != nullptr) {
		}


		auto triggersLength = triggers.size();
		auto groups = std::vector<Group>(triggersLength);
		auto eventTypes = std::vector<GroupEventType>(triggersLength);
		for(int i = 0; i < triggersLength; i++) {
			auto trigger = triggers[i];
			groups[i] = pool->GetGroup(trigger->trigger);
			eventTypes[i] = trigger->eventType;
		}
	}

	void ReactiveSystem::Activate() {
		_observer->Activate();
	}

	void ReactiveSystem::Deactivate() {
		_observer->Deactivate();
	}

	void ReactiveSystem::Clear() {
		_observer->ClearCollectedEntities();
	}

	void ReactiveSystem::Execute() {
		if(_observer->GetcollectedEntities().size() != 0) {
			if(_ensureComponents != nullptr) {
				if(_excludeComponents != nullptr) {
					for(auto e : _observer->GetcollectedEntities()) {
						if(_ensureComponents->Matches(e) && !_excludeComponents->Matches(e))
							_buffer.push_back(e->Retain(shared_from_this()));
					}
				} else {
					for(auto e : _observer->GetcollectedEntities()) {
						if(_ensureComponents->Matches(e))
							_buffer.push_back(e->Retain(shared_from_this()));
					}
				}
			} else if(_excludeComponents != nullptr) {
				for(auto e : _observer->GetcollectedEntities()) {
					if(!_excludeComponents->Matches(e))
						_buffer.push_back(e->Retain(shared_from_this()));
				}
			} else {
				for(auto e : _observer->GetcollectedEntities())
					_buffer.push_back(e->Retain(shared_from_this()));
			}

			_observer->ClearCollectedEntities();
			if(_buffer.size() != 0) {
				_subsystem->Execute(_buffer);
				for(int i = 0, bufferCount = _buffer.size(); i < bufferCount; i++)
					_buffer[i]->Release(shared_from_this());
				_buffer.clear();
				if(_clearAfterExecute)
					_observer->ClearCollectedEntities();
			}
		}
	}
}
