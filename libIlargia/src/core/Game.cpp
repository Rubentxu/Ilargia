#include "core/Game.h"

namespace Ilargia {

    int Game::runGame() {
        _timer->start();
        while (isRunning()) {
            //processGameEvents(_engine.getEvents());
            _engine->processInput();
            if(!_timer->paused())_engine->update(_timer->step());
            _engine->render();

        }
        _timer->stop();
        return getErrorState();
    }

    void Game::pushState(GameStatePtr gameState) {
        _states.push(std::move(gameState));
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

    void Game::changeState(GameStatePtr gameState) {
        if (!_states.empty()) {
            popState();
        }
        pushState(std::move(gameState));

    }

    void Game::clear() {
        while (!_states.empty()) {
            _states.pop();
        }

    }

}