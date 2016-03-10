#ifndef ILARGIA_GAME_STATE_H
#define ILARGIA_GAME_STATE_H

#include <types.hpp>

namespace Ilargia {

    class GameStateStack;

    class GameState {
        Game *_game;
    public:
        GameState() = delete;

        GameState(Game* game) : _game(game) { }

        virtual ~GameState() = 0;

        Game &getGame() { return *_game; }

        const Game &getGame() const { return *_game; }

        virtual void init() { }

        virtual void loadResources() { }

        virtual void unloadResources() { }

        virtual void update(Ilargia::Seconds deltaTime) { }

        virtual void render() { }

        virtual void onPause() { }

        virtual void onResume() { }

    };

}

#endif // ILARGIA_GAME_STATE_H
