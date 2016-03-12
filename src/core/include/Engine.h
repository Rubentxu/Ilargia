#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

namespace Ilargia {

    class Engine {
        int _errorState;
        bool _hasShutdown;
    public:
        virtual void configure() =0;

        virtual void initSystems() =0;

        virtual void processInput() = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render() = 0;

        virtual void shutdown(int errorCode) {
            _errorState = errorCode;
            _hasShutdown = true;
        }

        template <typename T>
        virtual T* getSystem() =0;

        //virtual std::deque<Event> getEvents() const { return _errorState; }

        virtual int getErrorState() const { return _errorState; }

        virtual bool hasShutdown() const { return _hasShutdown; }

    };
}
#endif // ILARGIA_ENGINE_H
