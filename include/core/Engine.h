#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>


namespace Ilargia {

    class Manager {
    public:
        virtual ~Manager() { }
    };

    class System {
    public:
        virtual void update(float deltaTime) = 0;

        virtual ~System() { }
    };

    class Engine {
        static int s_nextTypeSystemId;
        static int s_nextTypeManagerId;

        template<typename T>
        static int getTypeSystemID() {
            static int typeId = s_nextTypeSystemId++;
            return typeId;
        }

        template<typename T>
        static int getTypeManagerID() {
            static int typeId = s_nextTypeManagerId++;
            return typeId;
        }

    protected:
        std::vector<std::unique_ptr<Manager>> _managers;
        std::vector<std::unique_ptr<System>> _systems;

        int _errorState;
        bool _hasShutdown;

    public:

        template <class T>
        Engine(std::unique_ptr<T> n) {
            addDelegate(std::forward(n));
        }

        template <class T, class... T2>
        Engine(std::unique_ptr<T> n, std::unique_ptr<T2>... rest) {
            addDelegate(n);
            Engine(std::forward(rest)...);
        }

        template <class T>
        void addDelegate(std::unique_ptr<T> n) {
            if(dynamic_cast<Manager *>(n.get()))
                _managers.push_back(std::forward(n));
            if(dynamic_cast<System *>(n.get()))
                _systems.push_back(std::forward(n));
        }

        Engine() { };

        Engine &operator=(const Engine &other) = delete;

        virtual void configure(std::vector<std::string> &args) = 0;

        virtual void initSystems() = 0;

        virtual void processInput() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;

        virtual void shutdown() = 0;

        void shutdownEngine(int errorCode) {
            _errorState = errorCode;
            _hasShutdown = true;
            shutdown();
        }

        int getErrorState() const { return _errorState; }

        bool hasShutdown() const { return _hasShutdown; }


        template<typename S>
        std::unique_ptr<S>& getSystem() {
            auto typeId = getTypeSystemID<S>();
            return _systems[typeId];
        }

        template<typename M>
        std::unique_ptr<M>& getManager() {
            auto typeId = getTypeManagerID<M>();
            return _managers[typeId];
        }
    };
}
#endif // ILARGIA_ENGINE_H
