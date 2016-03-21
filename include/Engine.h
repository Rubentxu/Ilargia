#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <anax/anax.hpp>
#include "AssetManager.h"
#include "SDLUtil.h"

namespace Ilargia {

    class Engine {
    protected:
        int _errorState;
        bool _hasShutdown;
        std::unique_ptr<anax::World> _world;
        WindowPtr _window;
        std::shared_ptr<AssetManager> _assetManager;

    public:
        void configure();

        void initSystems();

        void processInput();

        void update(float deltaTime);

        void render();

        void shutdown(int errorCode);

        //virtual std::deque<Event> getEvents() const { return _errorState; }

        int getErrorState() const { return _errorState; }

        bool hasShutdown() const { return _hasShutdown; }
        
        std::unique_ptr<anax::World>& getWorld() {
            return _world;
        }
        
        std::shared_ptr<AssetManager>& getAssetManager() {
            return _assetManager;
        }

    };
}
#endif // ILARGIA_ENGINE_H
