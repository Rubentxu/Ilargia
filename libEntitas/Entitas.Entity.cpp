#include "Entitas.Entity.h"
#include "Entity.h"
#include "IComponent.h"


namespace Entitas {

	const int &Entity::GetcreationIndex() const {
		return _creationIndex;
	}

	Entity::Entity(int totalComponents) : _components(std::vector<IComponent>(totalComponents)) {
	}

	std::shared_ptr<Entity> Entity::AddComponent(int index, const std::shared_ptr<IComponent> &component) {
		if(!_isEnabled)
			throw EntityIsNotEnabledException("Cannot add component!");

		if(HasComponent(index)) {
			std::string errorMsg;
			if(componentNames.empty())
				//errorMsg = std::string("Cannot add component at index ") + index + std::string(" to ") + shared_from_this();
			else
				//errorMsg = std::string("Cannot add component ") + componentNames[index] + std::string(" to ") + shared_from_this();

			throw EntityAlreadyHasComponentException(errorMsg, index);
		}

		_components[index] = component;
		_componentsCache.clear();
		_componentIndicesCache.clear();
		_toStringCache = _TEXT("");
		if(OnComponentAdded != nullptr) {
			for(auto listener : OnComponentAdded->listeners())
				listener(this, index, component);
		}

		return shared_from_this();
	}

	std::shared_ptr<Entity> Entity::RemoveComponent(int index) {
		if(!_isEnabled)
			throw EntityIsNotEnabledException("Cannot remove component!");

		if(!HasComponent(index)) {
			std::string errorMsg;
			if(componentNames.empty())
				errorMsg = std::string("Cannot remove component at index ") + index + std::string(" from ") + shared_from_this();
			else
				errorMsg = std::string(_TEXT("Cannot remove component ")) + componentNames[index] + std::string(_TEXT(" from ")) + shared_from_this();

			throw EntityDoesNotHaveComponentException(errorMsg, index);
		}

		replaceComponent(index, nullptr);

		return shared_from_this();
	}

	std::shared_ptr<Entity> Entity::ReplaceComponent(int index, const std::shared_ptr<IComponent> &component) {
		if(!_isEnabled)
			throw EntityIsNotEnabledException(_TEXT("Cannot replace component!"));

		if(HasComponent(index))
			replaceComponent(index, component);
		else if(component != nullptr)
			AddComponent(index, component);

		return shared_from_this();
	}

	void Entity::replaceComponent(int index, const std::shared_ptr<IComponent> &replacement) {
		auto previousComponent = _components[index];
		if(previousComponent == replacement) {
			if(OnComponentReplaced != nullptr) {
				for(auto listener : OnComponentReplaced->listeners())
					listener(this, index, previousComponent, replacement);
			}
		} else {
			_components[index] = replacement;
			_componentsCache.clear();
			if(replacement == nullptr) {
				_componentIndicesCache.clear();
				_toStringCache = _TEXT("");
				if(OnComponentRemoved != nullptr) {
					for(auto listener : OnComponentRemoved->listeners())
						listener(this, index, previousComponent);
				}
			} else {
				if(OnComponentReplaced != nullptr) {
					for(auto listener : OnComponentReplaced->listeners())
						listener(this, index, previousComponent, replacement);
				}
			}
		}
	}

	std::shared_ptr<IComponent> Entity::GetComponent(int index) {
		if(!HasComponent(index)) {
			std::string errorMsg;
			if(componentNames.empty())
				errorMsg = std::string(_TEXT("Cannot get component at index ")) + index + std::string(_TEXT(" from ")) + shared_from_this();
			else
				errorMsg = std::string(_TEXT("Cannot get component ")) + componentNames[index] + std::string(_TEXT(" from ")) + shared_from_this();

			throw EntityDoesNotHaveComponentException(errorMsg, index);
		}

		return _components[index];
	}

	std::vector<IComponent> Entity::GetComponents() {
		if(_componentsCache.empty()) {
			auto components = std::vector<IComponent>(16);
			for(int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
				auto component = _components[i];
				if(component != nullptr)
					components.push_back(component);
			}

			_componentsCache = components.ToArray();
		}

		return _componentsCache;
	}

	std::vector<int> Entity::GetComponentIndices() {
		if(_componentIndicesCache.empty()) {
			auto indices = std::vector<int>(16);
			for(int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
				if(_components[i] != nullptr)
					indices.push_back(i);
			}

			_componentIndicesCache = indices.ToArray();
		}

		return _componentIndicesCache;
	}

	bool Entity::HasComponent(int index) {
		return _components[index] != nullptr;
	}

	bool Entity::HasComponents(std::vector<int> &indices) {
		for(int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
			if(_components[indices[i]] == nullptr)
				return false;
		}

		return true;
	}

	bool Entity::HasAnyComponent(std::vector<int> &indices) {
		for(int i = 0, indicesLength = indices.size(); i < indicesLength; i++) {
			if(_components[indices[i]] != nullptr)
				return true;
		}

		return false;
	}

	void Entity::RemoveAllComponents() {
		_toStringCache = _TEXT("");
		for(int i = 0, componentsLength = _components.size(); i < componentsLength; i++) {
			if(_components[i] != nullptr)
				replaceComponent(i, nullptr);
		}
	}

	void Entity::destroy() {
		RemoveAllComponents();
		OnComponentAdded->addListener(_TEXT("nullptr"), nullptr);
		OnComponentReplaced->addListener(_TEXT("nullptr"), nullptr);
		OnComponentRemoved->addListener(_TEXT("nullptr"), nullptr);
		componentNames.clear();
		_isEnabled = false;
	}

	std::string Entity::ToString() {
		if(_toStringCache == _TEXT("")) {
			auto sb = (std::make_shared<StringBuilder>())->Append(_TEXT("Entity_"))->Append(_creationIndex)->Append(_TEXT("("))->Append(GetretainCount())->Append(_TEXT(")"))->Append(_TEXT("("));

			constexpr std::string SEPARATOR = _TEXT(", ");
			auto components = GetComponents();
			auto lastSeparator = components.Length - 1;
			for(int i = 0, componentsLength = components.Length; i < componentsLength; i++) {
				sb->Append(components[i]->GetType()->RemoveComponentSuffix());
				if(i < lastSeparator)
					sb->Append(SEPARATOR);
			}

			sb->Append(_TEXT(")"));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			_toStringCache = sb->ToString();
		}

		return _toStringCache;
	}

	const int &Entity::GetretainCount() const {
		return owners.size();
	}

	std::shared_ptr<Entity> Entity::Retain(const std::shared_ptr<void> &owner) {
		if(!owners.insert(owner))
			throw EntityIsAlreadyRetainedByOwnerException(owner);

		return shared_from_this();
	}

	void Entity::Release(const std::shared_ptr<void> &owner) {
		if(!owners.Remove(owner))
			throw EntityIsNotRetainedByOwnerException(owner);

		if(owners.empty()) {
			if(OnEntityReleased != nullptr) {
				for(auto listener : OnEntityReleased->listeners())
					listener(this);
			}
		}
	}
}
