#include <memory>
#include "SDL2Engine.h"

namespace Ilargia {
    void SDL2Engine::configure() {
        if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
            _window = WindowPtr(SDL_CreateWindow("Testing Ilargia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                 640, 480, SDL_WINDOW_SHOWN));
            SDL_Renderer* _renderer;
            if (_window) {
                _renderer = SDL_CreateRenderer(_window.get(), -1, 0);
                _assetManager = std::make_shared<AssetManager> (_renderer);
                world = std::unique_ptr<anax::World>(new anax::World());
                RenderSystem renderingSystem {_assetManager};
                world->addSystem(renderingSystem);
            }
        }
        else {
            Engine::shutdown(1);
        }

    }

    void SDL2Engine::processInput() {
        SDL_Event event;
        if(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    shutdown(0);
                    break;
                default:
                    break;
            }
        }
    }

    void SDL2Engine::shutdown(int errorCode) {
        Engine::shutdown(errorCode);
        _window.reset();    //SDL_DestroyWindow(iWindow);
        world->removeSystem<RenderSystem>();
        SDL_Quit();
    }


}

