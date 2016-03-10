#ifndef ILARGIA_STATED_GAME_H
#define ILARGIA_STATED_GAME_H

#include <GameState.h>
#include <GameStateStack.h>

namespace Ilargia {

    class Game {
        GameStateStack _states;
        std::unique_ptr <Engine> _engine;

        virtual void configureEngine() = 0;

        virtual void frameStart() = 0;

        void update(Ilargia::Seconds deltaTime) {
            _stack.update(deltaTime);
        }

        void frameEnd() {
            _stack.render();
        }

    public:
        Game(Engine &&engine) : _engine{std::move(engine)} { }

        GameStateStack &getGameStateStack() { return _stack; }

        const GameStateStack &getGameStateStack() const { return _stack; }

        std::unique_ptr <Engine> &getEngine() const { return _engine; }

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        virtual void init(int argc, char *argv[]) {
            configureEngine();
        }

        int runGame() {
            const float MAX_FRAME_TIME = 1 / 4.f;
            const float DELTA_TIME = 1 / 60.f;
            Seconds currentTime = 0;
            Seconds accumulator = 0;

            while (isRunning()) {
                frameStart();

                Seconds newTime = pine::time_now();
                Seconds frameTime = newTime - currentTime;
                currentTime = newTime;

                if (frameTime >= MAX_FRAME_TIME) {
                    frameTime = MAX_FRAME_TIME;
                }

                accumulator += frameTime;

                // Update our game
                while (accumulator >= DELTA_TIME) {
                    update(DELTA_TIME);
                    accumulator -= DELTA_TIME;
                }
                frameEnd();
            }
            return game.getErrorState();
        }

    };
}

#endif // ILARGIA_STATED_GAME_H
