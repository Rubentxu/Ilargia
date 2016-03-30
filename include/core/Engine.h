#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>


namespace Ilargia {

    template <class M>
    struct ManagerPtr {
        std::unique_ptr<M> _manager;
    };

    template <class... ManagerPtrs>
    struct Managers: ManagerPtrs... {};

    template <class S>
    struct SystemPtr {
        std::unique_ptr<S> _system;
    };

    template <class... SystemPtrs>
    struct Systems: SystemPtrs... { };


    class Engine: public Managers<>, public Systems<>  {
    protected:
        int _errorState;
        bool _hasShutdown;

    public:

        Engine() {};

        Engine(const Engine& other) = delete;

        Engine& operator=(const Engine& other) = delete;

        virtual void configure(std::vector<std::string>& args) = 0;

        virtual void initSystems() = 0;

        virtual void processInput() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;

        virtual void shutdown() = 0;

        void shutdownEngine(int errorCode){
            _errorState = errorCode;
            _hasShutdown = true;
            shutdown();
        }

        int getErrorState() const { return _errorState; }

        bool hasShutdown() const { return _hasShutdown; }


        template <class M>
        std::unique_ptr<M>& getManager() {
            static_assert(std::is_base_of<ManagerPtr<M>, Managers>::value,
                    "Please ensure that this type or this key exists in this repository");
            return ManagerPtr<M>::_manager;
        }

        template <class S>
        std::unique_ptr<S>& getSystem() {
            static_assert(std::is_base_of<ManagerPtr<S>, Systems>::value,
                          "Please ensure that this type or this key exists in this repository");
            return SystemPtr<S>::_system;
        }

    };
}
#endif // ILARGIA_ENGINE_H
