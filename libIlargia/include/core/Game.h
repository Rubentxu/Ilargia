#ifndef ILARGIA_GAME_H
#define ILARGIA_GAME_H

#include <memory>
#include <stack>
#include "Engine.h"
#include "GameState.h"
#include "Timer.h"

namespace Ilargia {

    class Game {

        using  GameStatePtr = std::shared_ptr<GameState> ;
        std::stack<GameStatePtr> _states;
        std::shared_ptr<Engine> _engine;
        std::shared_ptr<Timer> _timer;
        unsigned int thisTime = 0;
        unsigned int lastTime = 0;

    public:
        Game(std::shared_ptr<Engine> engine, std::shared_ptr<Timer> timer)
                : _engine(engine), _timer(timer) {}

        int getErrorState() const { return _engine->getErrorState(); }

        bool isRunning() const { return !_engine->hasShutdown(); }

        void init(int argc, char *argv[]) {
            std::vector<std::string> args;
            for (int i=1;i<argc;i++){
                args.push_back(std::string(argv[i]));
            }
            _engine->configure(args);
            _engine->initSystems();
        }

        //virtual void processGameEvents(std::deque events) =0;

        int runGame();

        void pushState(GameStatePtr gameState);

        void popState();

        void changeState(GameStatePtr gameState);

        void clear();
    };
}

#endif // ILARGIA_GAME_H
