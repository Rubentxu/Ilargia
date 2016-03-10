#ifndef ILARGIA_GAMESTATESTACK_H
#define ILARGIA_GAMESTATESTACK_H

#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <cassert>

#include <GameState.h>

namespace Ilargia {


    class GameStateStackListener {
    public:
        virtual ~GameStateStackListener() { }

        virtual void onGameStatePushed(GameStateStack &sender, GameStateStack::State &gameState) { }

        virtual void onStackWillBePopped(GameStateStack &sender) { }

        virtual void onStackCleared(GameStateStack &sender) { }
    };



    class GameStateStack {

        // utility class used to delete game states
        struct GameStateDeleter {
            void operator()(State *gameState) const {
                // unload resources
                gameState->unloadResources();

                // delete the game state
                delete gameState->_game;
                delete gameState;
            }
        };

        using  GameStatePtr = std::unique_ptr <GameState, GameStateDeleter> ;

        /// Objecst that listen to game state events
        std::vector<std::unique_ptr<Listener> _listeners;

        /// The underlying stack implementation
        std::stack<GameStatePtr> _stack;

        /// The game attached to the stack
        Game *_game;

    public:
        explicit GameStateStack(Game* game, GameState *gameState = nullptr) :
                _game(&game) {
            if (gameState) push(gameState);
        }

        ~GameStateStack() { clear(); }

        void push(GameState *gameState) {
            assert(gameState && "GameState is null, please offer a non-null GameState");

            for (auto &listener : _listeners) {
                listener->onGameStatePushed(*this, *gameState);
            }

            _stack.emplace_back(GameStatePtr{gameState});
            gameState->_game = _game;

            // load resources
            gameState->loadResources();

            // initialize the state
            gameState->init();

            gameState->onResume();
        }

        /// Pops the GameState stack
        void pop() {
            if (_stack.empty()) return;

            for (auto &listener : _listeners) {
                listener->onStackPopped(*this);
            }
            auto gameState = _stack.pop_back();
            gameState->onResume();

        }

        void update(Seconds deltaTime) {
            perform_f_on_stack([&](State *state) { state->update(deltaTime); });
        }

        void render() {
            perform_f_on_stack([](State *state) { state->render(); });
        }

        /// Clears the GameStateStack
        void clear() {
            for (auto &listener : _listeners) {
                listener->onStackWillBeCleared(*this);
            }

            _stack.clear();
        }

        /// Removes a GameState from the stack
        /// \param gameState The GameState you wish to remove
        void remove(State *gameState) {
            assert(gameState);

            auto elementToRemove = std::find_if(_stack.begin(), _stack.end(),
                                                [&](GameStatePair &p) { return p.first.get() == gameState; });

            if (elementToRemove == _stack.end())
                return;

            for (auto &listener : _listeners) {
                listener->onGameStateWillBeRemoved(*this, gameState);
            }

            _stack.erase(elementToRemove);
        }


        /// \return The Game that the GameStack is connected to
        Game &getGame() const { return *_game; }

        /// Adds a listener to the GameStateStack
        /// \param listener The listener you wish to add to the game state stack
        void addListener(Listener *listener) {
            assert(listener);
            _listeners.push_back(listener);
        }

        /// Removes a listener to the GameStateStack
        /// \param listener The listener you wish to remove from the game state stack
        void removeListener(Listener *listener) {
            assert(listener);
            _listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
        }



    };
}

#endif // ILARGIA_GAMESTATESTACK_H
