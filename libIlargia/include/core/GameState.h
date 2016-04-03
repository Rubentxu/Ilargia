#ifndef ILARGIA_GAME_STATE_H
#define ILARGIA_GAME_STATE_H

#include "Engine.h"

namespace Ilargia {

    class GameState {
        std::shared_ptr<Engine> _engine;
    public:
        GameState(std::shared_ptr<Engine> engine) : _engine(engine) {}

        virtual void loadResources()  = 0;

        virtual void init()  = 0;

        virtual void onResume() = 0;

        virtual void onPause() = 0;

        virtual void unloadResources() = 0;

    };

}

#endif // ILARGIA_GAME_STATE_H
