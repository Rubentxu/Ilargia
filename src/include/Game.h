#ifndef ILARGIA_STATED_GAME_H
#define ILARGIA_STATED_GAME_H

#include "GameStateStack.h"
#include "Engine.h"

namespace Ilargia {

    class Game {
        std::unique_ptr<GameStateStack> _stack;
        std::unique_ptr<Engine> _engine;

    public:
        Game(Engine &&engine) : _engine(&engine) { }

        std::unique_ptr<Engine>& getEngine() { return _engine; }

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        virtual void init(int argc, char *argv[]) {
            _engine->configureEngine();
        }

        float deltaTime();

        int runGame() {
            const float MAX_FRAME_TIME = 1000 / 4.f;
            const float DELTA_TIME = 1000 / 60.f;
            float accumulator{0};

            while (isRunning()) {
                _stack->frameStart();

                float frameTime = deltaTime();

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
