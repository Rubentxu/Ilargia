#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>
#include "core/Manager.h"

namespace Ilargia {


    class Engine {
        static int s_nextTypeManagerId;

        template<typename T>
        static int getTypeManagerID() {
            static int typeId = s_nextTypeManagerId++;
            return typeId;
        }

    protected:
        std::vector<std::shared_ptr<Manager>> _managers;

        int _errorState;
        bool _hasShutdown;

    public:

        template <class T>
        Engine(std::shared_ptr<T> n) {
            _managers[getTypeManagerID<T>] = n;
        }

        template <class T, class... T2>
        Engine(std::shared_ptr<T> n, std::shared_ptr<T2>... rest) {
            _managers[getTypeManagerID<T>] = n;
            Engine(std::forward(rest)...);
        }

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

        template<typename M>
        std::unique_ptr<M>& getManager() {
            auto typeId = getTypeManagerID<M>();
            return _managers[typeId];
        }
    };
}
#endif // ILARGIA_ENGINE_H
