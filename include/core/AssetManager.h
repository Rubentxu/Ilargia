#ifndef __AssetManager__
#define __AssetManager__

#include <string>
#include <unordered_map>


namespace Ilargia {

    template <class Value, class Key = std::string>
    class AssetMap {
    protected:
        struct Free_Functor {
            void operator() (Value *ptr);
        };
        std::unordered_map<Key, std::unique_ptr<Value,Free_Functor>> _map;
    public:
        template <typename... Args>
        bool loadAsset(std::string fileName, Key id,Args... args);

        Value* &getAsset(Key id) {
            auto it = _map.find(id);
            if (it == _map.end()) {
                auto result = _map.insert(std::make_pair(id, std::unique_ptr<Value,Free_Functor>(Value{})));
                return result.first->second.get();
            }
            return it->second.get();
        }

        void clearAssets() {
            _map.clear();
        }

    };


    template <class... AssetMaps>
    class AssetManager : AssetMaps... {

    public:

        AssetManager();

        AssetManager(const AssetManager &) = delete;

        AssetManager &operator=(const AssetManager &) = delete;

        ~AssetManager() {

        }

        template <class Value, class Key = std::string>
        void loadAsset(std::string fileName, Key id) {
            static_assert(std::is_base_of<AssetMap<Value, Key>, AssetManager<AssetMaps...>>::value,
                    "Please ensure that this type or this key exists in this repository");
            AssetMap<Value, Key>::loadAsset(fileName,id);
        }

        template <class Value, class Key = std::string>
        std::unique_ptr<Value>& getAsset(Key id) {
            static_assert(std::is_base_of<AssetMap<Value, Key>, AssetManager<AssetMaps...>>::value,
                          "Please ensure that this type or this key exists in this repository");
            AssetMap<Value, Key>::getAsset(id);
        }

    };
}
#endif