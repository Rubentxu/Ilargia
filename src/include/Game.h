#ifndef ILARGIA_STATED_GAME_H
#define ILARGIA_STATED_GAME_H

#include <memory>
#include "GameStateStack.h"
#include "Engine.h"

namespace Ilargia {

    class Game {
        std::unique_ptr<Engine> _engine;
        std::unique_ptr<GameStateStack> _stack;

    public:
        Game(Engine &&engine, GameState &&gameState) : _engine(&engine), _stack(new GameStateStack(std::move(gameState))) { }

        std::unique_ptr<Engine>& getEngine() { return _engine; }

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        void init(int argc, char *argv[]) {
            _engine->configure();
        }

        //virtual void processGameEvents(std::deque events) =0;

        float deltaTime();

        int runGame() {
            const float MAX_FRAME_TIME = 1000 / 4.f;
            const float DELTA_TIME = 1000 / 60.f;
            float accumulator{0};

            while (isRunning()) {
                //processGameEvents(_engine.getEvents());
                _engine->processInput();

                float frameTime = deltaTime();

                if (frameTime >= MAX_FRAME_TIME) {
                    frameTime = MAX_FRAME_TIME;
                }
                accumulator += frameTime;

                while (accumulator >= DELTA_TIME) {
                    _engine->update(DELTA_TIME);
                    accumulator -= DELTA_TIME;
                }
                _engine->render();
            }
            return getErrorState();
        }
    };
}

#endif // ILARGIA_STATED_GAME_H
