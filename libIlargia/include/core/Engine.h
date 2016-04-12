#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>
#include "core/Manager.h"

namespace Ilargia {

    template<int N, typename Base>
    class ArrayIndex {
       // static const int size = sizeof...(Args);
        std::array<Base,N> _data;
        static int s_nextTypeId;

        template<typename T>
        void addItem(T &&item) {
            static_assert(!std::is_lvalue_reference<T>::value,
                          "T replacement template argument must be a reference type rvalue");
            int id = getTypeID<T>();
            //_data[id] = std::forward<T>(item);

        }



    public:

        template<typename... Ts>
        ArrayIndex(Ts&&... vs) : _data{{std::forward<Ts>(vs)...}} {
            static_assert(sizeof...(Ts)==N,"Not enough args supplied!");
            /* for(auto d: _data) {
               getTypeID<decltype(d)>();
           }*/
        }



        template<typename T>
        static int getTypeID() {
            static int typeId = s_nextTypeId++;
            return typeId;
        }

        template<typename T>
        T &get() {
            return static_cast<T &>(_data[getTypeID<T>()]);
        }

    };

    template<int N, typename Base>
    int ArrayIndex<N,Base>::s_nextTypeId = 0;

    class Engine {

    protected:
        std::vector<std::shared_ptr<Manager>> _managers;

        int _errorState;
        bool _hasShutdown;

    public:

        template<class... T>
        Engine(std::shared_ptr<T>... rest) {
            /*    constexpr int n = sizeof...(T);
                //_managers.reserve(n);
                _managers = {n,rest...};
                getTypeManagerID<T...>();*/

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

        /*  template<typename M>
          std::shared_ptr<M>& getManager() {
              return _managers[getTypeManagerID<M>()];
          }*/
    };
}
#endif // ILARGIA_ENGINE_H
