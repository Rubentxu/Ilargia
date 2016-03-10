#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

namespace Ilargia {

    class Engine {
        int _errorState;
        bool _hasShutdown;
    public:
        virtual void init(int argc, char *argv[]) =0;

        virtual void frameStart() = 0;

        virtual void update(Ilargia::Seconds deltaTime) = 0;

        virtual void frameEnd() = 0;

        virtual void shutdown(int errorCode) {
            _errorState = errorCode;
            _hasShutdown = true;
        }

        virtual int getErrorState() const { return _errorState; }

        virtual bool hasShutdown() const { return _hasShutdown; }

    };
}
#endif // ILARGIA_ENGINE_H
