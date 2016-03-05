#ifndef ENTITAS_EVENT
#define ENTITAS_EVENT

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace Entitas {

    enum class GroupEventType {
        OnEntityAdded,
        OnEntityRemoved,
        OnEntityAddedOrRemoved
    };

    template<typename T>
    class Event final {
        std::unordered_map<std::string, T> namedListeners;
        std::vector<T> anonymousListeners;
    public:
        void addListener(const std::string &methodName, T namedEventHandlerMethod) {
            if (namedListeners.find(methodName) == namedListeners.end())
                namedListeners[methodName] = namedEventHandlerMethod;
        }

        void removeListener(const std::string &methodName) {
            if (namedListeners.find(methodName) != namedListeners.end())
                namedListeners.erase(methodName);
        }

        void addListener(T unnamedEventHandlerMethod) {
            anonymousListeners.push_back(unnamedEventHandlerMethod);
        }

        std::vector<T> listeners() {
            std::vector<T> allListeners;
            for (auto listener : namedListeners) {
                allListeners.push_back(listener.second);
            }
            allListeners.insert(allListeners.end(), anonymousListeners.begin(), anonymousListeners.end());
            return allListeners;
        }

        void clear() {
            namedListeners.clear();
            anonymousListeners.clear();
        }
    };
}

#endif	//#ifndef ENTITAS_EVENT
