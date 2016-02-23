#ifndef EVENT
#define EVENT

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Entitas {
	namespace events {

		template<typename T>
		class Event final : public std::enable_shared_from_this<Event> {
		private:
			std::unordered_map<std::string, T> namedListeners;
			std::vector<T> anonymousListeners;

		public:
			void addListener(const std::string &methodName, T namedEventHandlerMethod) {
				if (namedListeners.find(methodName) == namedListeners.end()) {
					namedListeners[methodName] = namedEventHandlerMethod;
				}
			}


			void removeListener(const std::string &methodName) {
				if (namedListeners.find(methodName) != namedListeners.end()) {
					namedListeners.erase(methodName);
				}
			}


			void addListener(T unnamedEventHandlerMethod) {
				anonymousListeners.push_back(unnamedEventHandlerMethod);
			}


			std::vector<T> listeners() {
				std::vector<T> allListeners;
				allListeners.insert(allListeners.end(), namedListeners.begin(), namedListeners.end());
				allListeners.insert(allListeners.end(), anonymousListeners.begin(), anonymousListeners.end());
				return allListeners;
			}

			void clear() {
				namedListeners.clear();
				anonymousListeners.clear();
			}

		};
	}
}


#endif	//#ifndef EVENT
