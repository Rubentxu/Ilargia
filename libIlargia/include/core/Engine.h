#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>
#include "core/Manager.h"

namespace Ilargia {

    template<class Base>
    class TypeVector {
        static int s_nextTypeId;
        std::vector<Base> _data;

        template <class T>
        void addItem(T&& n) {
            static_assert(!std::is_lvalue_reference<T>::value,
                          "T replacement template argument must be a reference type rvalue");

            s_nextTypeId = _data.size();
            getTypeID<T>();
            _data.push_back(std::forward<T>(n));
        }

        template <class T, class... T2>
        void addItem(T&& n, T2&&... rest) {
            addItem(std::forward<T>(n));
            addItem(std::forward<T2>(rest)...);
        }


    public:
        template<typename... Ts>
        TypeVector(Ts &&... vs) {
            addItem(std::forward<Ts>(vs)...);
        }

        template<typename T>
        static int getTypeID() {
            static int typeId = s_nextTypeId;
            return typeId;
        }

        template<typename T>
        T &get() {
            return static_cast<T &>(_data[getTypeID<T>()]);
        }

    };

    template<class Base>
    int TypeVector<Base>::s_nextTypeId = 0;

    class Engine: public TypeVector<std::shared_ptr<Manager>>{

    protected:

        int _errorState;
        bool _hasShutdown;

    public:

        template<class... T>
        Engine(std::shared_ptr<T>&&... rest): TypeVector(std::forward<std::shared_ptr<T>>(rest)...) { }

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
