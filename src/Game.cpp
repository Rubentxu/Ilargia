#include "Game.h"
#include <SDL.h>

namespace Ilargia {     
    Uint32 thisTime = 0;
    Uint32 lastTime = 0;

    inline float Game::deltaTime() {
        thisTime = SDL_GetTicks();
        float deltaTime = (float) (thisTime - lastTime) / 1000;
        lastTime = thisTime;
        return deltaTime;
    }

}