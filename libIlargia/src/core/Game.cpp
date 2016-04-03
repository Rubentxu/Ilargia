#include "core/Game.h"
#include <SDL2pp/SDL2pp.hh>

namespace Ilargia {

    int Game::runGame() {
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
                accumulator -= DELTA_TIME;
            }
            _engine->update(DELTA_TIME);
            _engine->render();
        }
        return getErrorState();
    }

    inline float Game::deltaTime() {
        thisTime = SDL_GetTicks();
        float deltaTime = (float) (thisTime - lastTime) / 1000;
        lastTime = thisTime;
        return deltaTime;
    }

    void Game::pushState(GameState &&gameState) {
        _states.push(GameStatePtr(&gameState));
        _states.top()->loadResources();
        _states.top()->init();
        _states.top()->onResume();
    }

    void Game::popState() {
        if (_states.empty()) return;

        _states.top()->onPause();
        _states.top()->unloadResources();
        _states.pop();

    }

    void Game::changeState(GameState &&gameState) {
        if(!_states.empty()) {
            popState();
        }
        pushState(std::move(gameState));
    }

    /// Clears the GameStateStack
    void Game::clear() {
        while(!_states.empty()) {
            _states.pop();
        }

    }

}