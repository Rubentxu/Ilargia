#ifndef ILARGIA_GAME_STATE_H

#include "Engine.h"

namespace Ilargia {

    struct GameState {
        Engine *_engine;

        GameState() = delete;

        GameState(Engine *engine) : _engine{engine} {}

        virtual void loadResources(AssetManager& assetManager)  = 0;

        virtual void init(anax::World& world)  = 0;

        virtual void onResume(anax::World& world) = 0;

        virtual void onPause(anax::World& world) = 0;

        virtual void unloadResources(AssetManager& assetManager) = 0;


    };

}

#endif // ILARGIA_GAME_STATE_H
