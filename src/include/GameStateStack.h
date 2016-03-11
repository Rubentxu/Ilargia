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
                gameState->removeEngine();
                delete gameState;
            }
        };

        using  GameStatePtr = std::unique_ptr <GameState, GameStateDeleter> ;
        std::stack<GameStatePtr> _states;

        Engine *_engine;

    public:
        explicit GameStateStack(Engine* engine, GameState &&gameState) : _engine(engine) {
           pushState(std::move(gameState));
        }

        ~GameStateStack() { clear(); }

        void pushState(GameState &&gameState) {
            _states.push(GameStatePtr(&gameState));
            _states.top()->setEngine(_engine);
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

        void frameStart() {
            _states.top()->handleInput();
            _engine->frameStart();
        }

        void update(float deltaTime) {
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
