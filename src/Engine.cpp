#include <memory>
#include "Engine.h"
#include "Systems/RenderSystem.h"

namespace Ilargia {

    void Engine::configure() {
        int imgFlags = IMG_INIT_PNG;
        if (SDL_Init(SDL_INIT_EVERYTHING) >= 0 && (IMG_Init(imgFlags) & imgFlags)
                && TTF_Init() == -1) {
            _window = WindowPtr(SDL_CreateWindow("Testing Ilargia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    640, 480, SDL_WINDOW_SHOWN));

            SDL_Renderer* _renderer;
            if (_window) {
                _renderer = SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);
                _assetManager = std::make_shared<AssetManager> (_renderer);
                _world = std::unique_ptr<anax::World>(new anax::World());
                RenderSystem renderingSystem{_assetManager};
                _world->addSystem(renderingSystem);
            }
        } else {
            Engine::shutdown(1);
        }

    }

    void Engine::processInput() {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    shutdown(0);
                    break;
                default:
                    break;
            }
        }
    }

    void Engine::shutdown(int errorCode) {
        _errorState = errorCode;
        _hasShutdown = true;
        _window.reset(); //SDL_DestroyWindow(iWindow);
        _world->removeSystem<RenderSystem>();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }


}

