#ifndef RUNGAME_H
#define RUNGAME_H

#include <type_traits>
#include "Time.h"
#include <Game.h>

namespace Ilargia {

        template<class TGame>
        int RunGame(TGame &game) {
            static_assert(std::is_base_of<GameType, TGame>::value, "Game is not a GameType");

            const float MAX_FRAME_TIME = 1 / 4.f;
            const float DELTA_TIME = 1 / 60.f;
            Seconds currentTime = 0;
            Seconds accumulator = 0;

            while (game.isRunning()) {
                game.frameStart();

                Seconds newTime = Ilargia::time_now();
                Seconds frameTime = newTime - currentTime;
                currentTime = newTime;

                // cap the loop delta time
                if (frameTime >= MAX_FRAME_TIME) {
                    frameTime = MAX_FRAME_TIME;
                }

                accumulator += frameTime;

                // Update our game
                while (accumulator >= DELTA_TIME) {
                    game.update(DELTA_TIME); // update the game (with the constant delta time)
                    accumulator -= DELTA_TIME; // decrease the accumulator
                }

                game.frameEnd();
            }

            return game.getErrorState();
        }

        template<class TGame, class TEngine>
        struct GameRunner {
            int operator()(int argc, char *argv[]) {
                TEngine engine;
                TGame game;
                game.setEngine(engine);
                game.init(argc, argv);

                return detail::RunGame(game);
            }
        };

        template<class TGame>
        struct GameRunner<TGame, void> {
            int operator()(int argc, char *argv[]) {
                TGame game;
                game.init(argc, argv);

                return detail::RunGame(game);
            }
        };
    }

    // game with engine
    template<class TGame>
    int RunGame(int argc, char *argv[]) {
        return detail::GameRunner<TGame, typename TGame::Engine>()(argc, argv);
    }


#endif // Ilargia_RUNGAME_H
