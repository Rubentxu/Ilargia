#ifndef ILARGIA_GAME_STATE_H
#define ILARGIA_GAME_STATE_H

#include "Engine.h"
#include "AssetManager.h"
#include <anax/anax.hpp>

namespace Ilargia {

    class GameState {
    public:
        GameState() = default;

        virtual void loadResources(AssetManager& assetManager)  = 0;

        virtual void init(anax::World& world)  = 0;

        virtual void onResume(anax::World& world) = 0;

        virtual void onPause(anax::World& world) = 0;

        virtual void unloadResources(AssetManager& assetManager) = 0;

    };

}

#endif // ILARGIA_GAME_STATE_H
