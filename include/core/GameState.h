#ifndef ILARGIA_GAME_STATE_H
#define ILARGIA_GAME_STATE_H

#include "Engine.h"
#include "AssetsManager.h"
#include <anax/anax.hpp>

namespace Ilargia {

    class GameState {
    public:
        GameState() = default;

        virtual void loadResources(Engine& engine)  = 0;

        virtual void init(Engine& engine)  = 0;

        virtual void onResume(Engine& engine) = 0;

        virtual void onPause(Engine& engine) = 0;

        virtual void unloadResources(Engine& engine) = 0;

    };

}

#endif // ILARGIA_GAME_STATE_H
