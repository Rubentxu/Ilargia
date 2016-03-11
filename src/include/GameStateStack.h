#ifndef ILARGIA_GAMESTATESTACK_H
#define ILARGIA_GAMESTATESTACK_H

#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <cassert>

#include <GameState.h>

namespace Ilargia {

    class GameStateStack {

        // utility class used to delete game states
        struct GameStateDeleter {
            void operator()(GameState *gameState) const {

                delete gameState->removeEngine();
                delete gameState;
            }
        };

        using  GameStatePtr = std::unique_ptr <GameState, GameStateDeleter> ;
        std::stack<GameStatePtr> _states;

        Engine *_engine;

    public:
        explicit GameStateStack(Engine* engine, GameState &&gameState = nullptr) : _engine(engine) {
            if (gameState) pushState(GameStatePtr(&gameState));
        }

        ~GameStateStack() { clear(); }

        void pushState(GameState &&gameState) {
            assert(gameState && "GameState is null, please offer a non-null GameState");

            _states.push(GameStatePtr(&gameState));
            _states.top().setEngine(_engine);
            _states.top().loadResources();
            _states.top().init();
            _states.top().onResume();
        }

        /// Pops the GameState stack
        void popState() {
            if (_states.empty()) return;

            _states.top()->onPause();
            _states.top()->unloadResources();
            _states.pop();

        }

        void changeState(GameState &&gameState) {
            if(!_states.empty())
                popState();
            pushState(std::move(state));
        }

        void frameStart() {
            _states.top()->handleInput();
            _engine->frameStart();
        }

        void update(Time deltaTime) {
            _engine->update(deltaTime);
            _states.top()->update(deltaTime);

        }

        void frameEnd() {
            _states.top()->render();
            _engine->frameEnd();
        }

        /// Clears the GameStateStack
        void clear() {
            while(!_states.empty()) {
                _states.pop();
            }

        }

    };
}

#endif // ILARGIA_GAMESTATESTACK_H
