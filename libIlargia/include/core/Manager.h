#ifndef __Manager__
#define __Manager__

#include <string>
#include <unordered_map>

namespace Ilargia {
    class Manager {
    public:
        virtual ~Manager() { }
    };

    template <class Value, class Key = std::string>
    class AssetMap {
    protected:

        bool storeAsset(Key id, Value value) {
             _map[id] = value;
        }

    public:
        void destroy (Value *ptr);

        std::unordered_map<Key,Value> _map;

        template <typename... Args>
        bool loadAsset(std::string fileName, Key id,Args... args);

        Value& getAsset(Key id) {
            auto it = _map.find(id);
            return it->second;
        }

        void clearAssets() {
            _map.clear();
        }

    };


    template <class... AssetMaps>
    class AssetManager : public Manager, public AssetMaps... {

    public:

        AssetManager();

        AssetManager(const AssetManager &) = delete;

        AssetManager &operator=(const AssetManager &) = delete;

        ~AssetManager() {

        }

        template <class Value, class Key = std::string>
        void loadAsset(std::string fileName, Key id) {

            AssetMap<Value, Key>::loadAsset(fileName,id);
        }

        template <class Value, class Key = std::string>
        Value& getAsset(Key id) {

            AssetMap<Value, Key>::getAsset(id);
        }

    };
}
#endif