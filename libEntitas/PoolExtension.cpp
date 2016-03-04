#include "PoolExtension.h"
#include "Entity.h"
#include "ISystem.h"
#include "Pool.h"
#include "IMatcher.h"
#include "IReactiveSystem.h"
#include "IMultiReactiveSystem.h"


namespace Entitas {

	std::vector<Entity> PoolExtension::GetEntities(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IMatcher> &matcher) {
		return pool->GetGroup(matcher)->GetEntities();
	}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T: ISystem, new()
	std::shared_ptr<ISystem> PoolExtension::CreateSystem(const std::shared_ptr<Pool> &pool) {
		return Entitas::PoolExtension::CreateSystem(pool, T::typeid);
	}

	std::shared_ptr<ISystem> PoolExtension::CreateSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<Type> &systemType) {
		auto system = std::static_pointer_cast<ISystem>(Activator::CreateInstance(systemType));
		return Entitas::PoolExtension::CreateSystem(pool, system);
	}

	std::shared_ptr<ISystem> PoolExtension::CreateSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<ISystem> &system) {
		setPool(system, pool);
		auto reactiveSystem = std::dynamic_pointer_cast<IReactiveSystem>(system);
		if(reactiveSystem != nullptr)
			return std::make_shared<ReactiveSystem>(pool, reactiveSystem);
		auto multiReactiveSystem = std::dynamic_pointer_cast<IMultiReactiveSystem>(system);
		if(multiReactiveSystem != nullptr)
			return std::make_shared<ReactiveSystem>(pool, multiReactiveSystem);

		return system;
	}

	void PoolExtension::setPool(const std::shared_ptr<ISystem> &system, const std::shared_ptr<Pool> &pool) {
		auto poolSystem = std::dynamic_pointer_cast<ISetPool>(system);
		if(poolSystem != nullptr)
			poolSystem->SetPool(pool);
	}
}
