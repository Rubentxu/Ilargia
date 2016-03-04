#ifndef SYSTEMS
#define SYSTEMS

#include <vector>
#include <memory>

namespace Entitas {
	class ISystem {};

	class Systems : public IInitializeSystem, public IExecuteSystem {

	protected:
		const std::vector<IInitializeSystem> _initializeSystems;
		const std::vector<IExecuteSystem> _executeSystems;

	public:
		Systems();

		template<typename T>
		std::shared_ptr<Systems> Add();

		virtual std::shared_ptr<Systems> Add(const std::shared_ptr<Type> &systemType);

		virtual std::shared_ptr<Systems> Add(const std::shared_ptr<ISystem> &system);

		virtual void Initialize();

		virtual void Execute();

		void ActivateReactiveSystems();

		void DeactivateReactiveSystems();

		virtual void ClearReactiveSystems();
	};


	class IExecuteSystem : public ISystem {
	public:
		virtual void Execute() = 0;
	};


	class IInitializeSystem : public ISystem {
	public:
		virtual void Initialize() = 0;
	};

	class IReactiveSystem : public IReactiveExecuteSystem {
	public:
		virtual const std::shared_ptr<TriggerOnEvent> &Gettrigger() const = 0;
	};

	class IMultiReactiveSystem : public IReactiveExecuteSystem {
	public:
		virtual std::vector<TriggerOnEvent> Gettriggers() const = 0;
	};

	class IReactiveExecuteSystem : public ISystem {
	public:
		virtual void Execute(std::vector<Entity> &entities) = 0;
	};

	class IEnsureComponents {
	public:
		virtual const std::shared_ptr<IMatcher> &GetensureComponents() const = 0;
	};

	class IExcludeComponents {
	public:
		virtual const std::shared_ptr<IMatcher> &GetexcludeComponents() const = 0;
	};

	class IClearReactiveSystem {
	};

	class ReactiveSystem : public IExecuteSystem {
		const std::shared_ptr<IReactiveExecuteSystem> _subsystem;
		const std::shared_ptr<GroupObserver> _observer;
		const std::shared_ptr<IMatcher> _ensureComponents;
		const std::shared_ptr<IMatcher> _excludeComponents;
		const bool _clearAfterExecute;
		const std::vector<Entity> _buffer;

		ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IReactiveExecuteSystem> &subSystem, std::vector<TriggerOnEvent> &triggers);

	public:
		ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IReactiveSystem> &subSystem);

		ReactiveSystem(const std::shared_ptr<Pool> &pool, const std::shared_ptr<IMultiReactiveSystem> &subSystem);

		const std::shared_ptr<IReactiveExecuteSystem> &Getsubsystem() const;

		void Activate();

		void Deactivate();

		void Clear();

		void Execute();
	};
}


#endif	//#ifndef SYSTEMS
