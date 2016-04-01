#ifndef PROJECT_IOCContainer_H
#define PROJECT_IOCContainer_H

#include <memory>
#include <vector>

class IOCContainer {
    static int s_nextTypeId;
public:
    template<typename T>
    static int getTypeID() {
        static int typeId = s_nextTypeId++;
        return typeId;
    }

    class FactoryRoot {
    public:
        virtual ~FactoryRoot() { }
    };

    std::vector<int, std::shared_ptr<FactoryRoot>> m_factories;

    template<typename T>
    class CFactory : public FactoryRoot {
        std::function<std::shared_ptr<T>()> m_functor;
    public:
        ~CFactory() { }

        CFactory(std::function<std::shared_ptr<T>()> functor) : m_functor(functor) { }

        std::shared_ptr<T> getObject() {
            return m_functor();
        }
    };

    template<typename T>
    std::shared_ptr<T> getObject() {
        auto typeId = getTypeID<T>();
        auto factoryBase = m_factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->getObject();
    }

    //Most basic implementation - register a functor
    template<typename TInterface, typename ...TS>
    void registerFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor) {
        m_factories[getTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
                [=] { return functor(getObject<TS>()...); });  }


    //Supply a function pointer
    template<typename TInterface, typename ...TS>
    void registerFunctor(std::shared_ptr<TInterface> (*functor)(std::shared_ptr<TS> ...ts)) {
        registerFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
    }

    //A factory that will call the constructor, per instance required
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void registerFactory() {
        registerFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
                        [](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface> {
                            return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
                        }));
    }

    //Register one instance of an object
    template<typename TInterface>
    void registerInstance(std::shared_ptr<TInterface> t) {
        m_factories[getTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] { return t; });
    }

    //A factory that will return one instance for every request
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void registerInstance() {
        registerInstance<TInterface>(std::make_shared<TConcrete>(getObject<TArguments>()...));
    }

};

#endif //PROJECT_IOCContainer_H
