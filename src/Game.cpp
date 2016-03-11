#include "Game.h"

namespace Ilargia {
    int Game::runGame() {
        const float MAX_FRAME_TIME = 1 / 4.f;
        const float DELTA_TIME = 1 / 60.f;
        Time currentTime = 0;
        Time accumulator = 0;

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
        return game.getErrorState();
    }
}


