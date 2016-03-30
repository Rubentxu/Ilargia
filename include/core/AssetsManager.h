#ifndef __AssetsManager__
#define __AssetsManager__

#include <string>
#include <unordered_map>


namespace Ilargia {

    template <class Value, class Key = std::string>
    class AssetMap {
    protected:
        virtual void destroy(Value* ptr) { if(ptr) delete ptr; }
        using AssetPtr = std::unique_ptr<Value,decltype(&destroy)>;
        std::unordered_map<Key, AssetPtr> _map;
    public:

        virtual bool loadAsset(std::string fileName, std::string id) = 0;

        Value* &getAsset(Key id) {
            auto it = _map.find(id);
            if (it == _map.end()) {
                auto result = _map.insert(std::make_pair(id, std::unique_ptr<Value,decltype(&destroy)>(Value{})));
                return result.first->second.get();
            }
            return it->second.get();
        }

        void clearAssets() {
            _map.clear();
        }

    };


    template <class... AssetMaps>
    class AssetsManager : AssetMaps... {

    public:

        AssetsManager();

        AssetsManager(const AssetsManager &) = delete;

        AssetsManager &operator=(const AssetsManager &) = delete;

        ~AssetsManager() {

        }

        template <class Value, class Key = std::string>
        void loadAsset(std::string fileName, Key id) {
            static_assert(std::is_base_of<AssetMap<Value, Key>, AssetsManager<AssetMaps...>>::value,
                    "Please ensure that this type or this key exists in this repository");
            AssetMap<Value, Key>::loadAsset(fileName,id);
        }

        template <class Value, class Key = std::string>
        std::unique_ptr<Value>& getAsset(std::string fileName, Key id) {
            static_assert(std::is_base_of<AssetMap<Value, Key>, AssetsManager<AssetMaps...>>::value,
                          "Please ensure that this type or this key exists in this repository");
            AssetMap<Value, Key>::getAsset(id);
        }

    };
}
#endif