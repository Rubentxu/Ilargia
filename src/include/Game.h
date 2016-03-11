#ifndef ILARGIA_STATED_GAME_H
#define ILARGIA_STATED_GAME_H

#include "GameState.h"
#include "GameStateStack.h"
#include "Time.h"
#include "Engine.h"

namespace Ilargia {

    class Game {
        std::unique_ptr<GameStateStack> _stack;
        std::unique_ptr<Engine> _engine;

    public:
        Game(Engine &&engine) : _engine{&std::move(engine)} { }

        std::unique_ptr<Engine>& getEngine() const { return _engine; }

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        virtual void init(int argc, char *argv[]) {
            _engine->configureEngine();
        }

        int runGame() {
            const float MAX_FRAME_TIME = 1 / 4.f;
            const float DELTA_TIME = 1 / 60.f;
            Time currentTime{0};
            Time accumulator{0};

            while (isRunning()) {
                _stack->frameStart();

                Time newTime = Ilargia::time_now();
                Time frameTime = newTime - currentTime;
                currentTime = newTime;

                if (frameTime >= MAX_FRAME_TIME) {
                    frameTime = MAX_FRAME_TIME;
                }
                accumulator += frameTime;

                while (accumulator >= DELTA_TIME) {
                    _stack->update(DELTA_TIME);
                    accumulator -= DELTA_TIME;
                }
                _stack->frameEnd();
            }
            return getErrorState();
        }

    };
}

#endif // ILARGIA_STATED_GAME_H
