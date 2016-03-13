#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <anax/anax.hpp>

namespace Ilargia {

    class Engine {
    protected:
        int _errorState;
        bool _hasShutdown;
        std::unique_ptr<anax::World> world;
    public:
        virtual void configure() {};

        virtual void initSystems() = 0;

        virtual void processInput() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;

        virtual void shutdown(int errorCode) {
            _errorState = errorCode;
            _hasShutdown = true;
        }

        //virtual std::deque<Event> getEvents() const { return _errorState; }

        virtual int getErrorState() const { return _errorState; }

        virtual bool hasShutdown() const { return _hasShutdown; }

    };
}
#endif // ILARGIA_ENGINE_H
