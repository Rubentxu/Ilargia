#ifndef ILARGIA_GAMESTATESTACK_H
#define ILARGIA_GAMESTATESTACK_H


#include <memory>
#include <cassert>
#include <stack>
#include "GameState.h"

namespace Ilargia {

    class GameStateStack {
        struct GameStateDeleter {
            void operator()(GameState *gameState) const {
                delete gameState->_engine;
                delete gameState;
            }
        };

        using  GameStatePtr = std::unique_ptr <GameState, GameStateDeleter> ;
        std::stack<GameStatePtr> _states;

    public:

        GameStateStack(GameState &&gameState) {
           pushState(std::move(gameState));
        }

        GameStateStack& operator= ( GameStateStack && ) = default;

        ~GameStateStack() { clear(); }

        void pushState(GameState &&gameState) {
            _states.push(GameStatePtr(&gameState));
            _states.top()->loadResources();
            _states.top()->init();
            _states.top()->onResume();
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
            pushState(std::move(gameState));
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
