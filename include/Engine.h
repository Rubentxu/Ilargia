#ifndef ILARGIA_ENGINE_H
#define ILARGIA_ENGINE_H

#include <memory>
#include <type_traits>
#include <vector>
#include <anax/anax.hpp>
#include "SDLUtil.h"
#include "AssetManager.h"
#include "Systems/RenderSystem.h"

namespace Ilargia {

    class Engine {
    protected:
        int _errorState;
        bool _hasShutdown;
        std::unique_ptr<anax::World> _world;
        WindowPtr _window;
        std::shared_ptr<AssetManager> _assetManager;
        RenderSystem renderingSystem;

    public:

        Engine() = default;

        void configure(std::vector<std::string>& args);

        void initSystems();

        void processInput();

        void update(float deltaTime);

        void render();

        void shutdown(int errorCode);

        //virtual std::deque<Event> getEvents() const { return _errorState; }

        int getErrorState() const { return _errorState; }

        bool hasShutdown() const { return _hasShutdown; }

        anax::World& getWorld() {
            return *_world;
        }
        
        AssetManager& getAssetManager() {
            return *_assetManager;
        }

    };
}
#endif // ILARGIA_ENGINE_H
