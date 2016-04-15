#include "core/Game.h"

namespace Ilargia {

    int Game::runGame() {
        const float STEP = _timer->Step();

        while (isRunning()) {
            //processGameEvents(_engine.getEvents());
            _engine->processInput();
            if(_timer->tick()) {
                _engine->update(STEP);
                _engine->render();
            }

        }
        return getErrorState();
    }

/*    inline float Game::deltaTime() {
        thisTime = deltaTime();
        float deltaTime = (float) (thisTime - lastTime) / 1000;
        lastTime = thisTime;
        return deltaTime;
    }*/

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