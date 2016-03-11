#ifndef ILARGIA_GAME_STATE_H

namespace Ilargia {

    class GameStateStack;

    class GameState {
        Engine *_engine;
    public:
        GameState() = default;

        void setEngine(Engine* engine) {
            _engine = engine;
        }

        void removeEngine() {
            delete _engine;
        }


        virtual ~GameState() = 0;

        virtual void loadResources()  = 0;

        virtual void init() = 0;

        virtual void onResume() = 0;

        virtual void onPause() = 0;

        virtual void unloadResources() = 0;

        virtual void handleInput() = 0;

        virtual void update(Ilargia::Time deltaTime) = 0;

        virtual void render() = 0;

    };

}

#endif // ILARGIA_GAME_STATE_H
