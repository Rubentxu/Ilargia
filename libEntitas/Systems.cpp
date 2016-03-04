#include "Systems.h"
#include "ReactiveSystem.h"
#include "ISystem.h"


namespace Entitas {

	Systems::Systems() : _initializeSystems(std::vector<IInitializeSystem>()), _executeSystems(std::vector<IExecuteSystem>()) {
	}

template<typename T>
	std::shared_ptr<Systems> Systems::Add() {
		return Add(T::typeid);
	}

	std::shared_ptr<Systems> Systems::Add(const std::shared_ptr<Type> &systemType) {
		return Add(std::static_pointer_cast<ISystem>(Activator::CreateInstance(systemType)));
	}

	std::shared_ptr<Systems> Systems::Add(const std::shared_ptr<ISystem> &system) {
		auto reactiveSystem = std::dynamic_pointer_cast<ReactiveSystem>(system);
		auto initializeSystem = reactiveSystem != nullptr ? std::dynamic_pointer_cast<IInitializeSystem>(reactiveSystem->Getsubsystem()) : std::dynamic_pointer_cast<IInitializeSystem>(system);

		if(initializeSystem != nullptr)
			_initializeSystems.push_back(initializeSystem);

		auto executeSystem = std::dynamic_pointer_cast<IExecuteSystem>(system);
		if(executeSystem != nullptr)
			_executeSystems.push_back(executeSystem);

		return shared_from_this();
	}

	void Systems::Initialize() {
		for(int i = 0, initializeSysCount = _initializeSystems.size(); i < initializeSysCount; i++)
			_initializeSystems[i]->Initialize();
	}

	void Systems::Execute() {
		for(int i = 0, exeSysCount = _executeSystems.size(); i < exeSysCount; i++)
			_executeSystems[i]->Execute();
	}

	void Systems::ActivateReactiveSystems() {
		for(int i = 0, exeSysCount = _executeSystems.size(); i < exeSysCount; i++) {
			auto reactiveSystem = std::dynamic_pointer_cast<ReactiveSystem>(_executeSystems[i]);
			if(reactiveSystem != nullptr)
				reactiveSystem->Activate();

			auto nestedSystems = std::dynamic_pointer_cast<Systems>(_executeSystems[i]);
			if(nestedSystems != nullptr)
				nestedSystems->ActivateReactiveSystems();
		}
	}

	void Systems::DeactivateReactiveSystems() {
		for(int i = 0, exeSysCount = _executeSystems.size(); i < exeSysCount; i++) {
			auto reactiveSystem = std::dynamic_pointer_cast<ReactiveSystem>(_executeSystems[i]);
			if(reactiveSystem != nullptr)
				reactiveSystem->Deactivate();

			auto nestedSystems = std::dynamic_pointer_cast<Systems>(_executeSystems[i]);
			if(nestedSystems != nullptr)
				nestedSystems->DeactivateReactiveSystems();
		}
	}

	void Systems::ClearReactiveSystems() {
		for(int i = 0, exeSysCount = _executeSystems.size(); i < exeSysCount; i++) {
			auto reactiveSystem = std::dynamic_pointer_cast<ReactiveSystem>(_executeSystems[i]);
			if(reactiveSystem != nullptr)
				reactiveSystem->Clear();

			auto nestedSystems = std::dynamic_pointer_cast<Systems>(_executeSystems[i]);
			if(nestedSystems != nullptr)
				nestedSystems->ClearReactiveSystems();
		}
	}
}
