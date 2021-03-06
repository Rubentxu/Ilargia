#ifndef ILARGIA_GAME_H
#define ILARGIA_GAME_H

#include <memory>
#include <stack>
#include "Engine.h"
#include "GameState.h"

namespace Ilargia {

    class Game {

        using  GameStatePtr = std::shared_ptr<GameState> ;
        std::stack<GameStatePtr> _states;
        std::shared_ptr<Engine> _engine;
        unsigned int thisTime = 0;
        unsigned int lastTime = 0;

    public:
        Game(std::shared_ptr<Engine> engine) : _engine(engine) {}

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        void init(int argc, char *argv[]) {
            std::vector<std::string> args;
            for (int i=1;i<argc;i++){
                args.push_back(argv[i]);
            }
            _engine->configure(args);
            _engine->initSystems();
        }

        //virtual void processGameEvents(std::deque events) =0;

        float deltaTime();

        int runGame();

        void pushState(GameState &&gameState);

        void popState();

        void changeState(GameState &&gameState);

        void clear();
    };
}

#endif // ILARGIA_GAME_H
