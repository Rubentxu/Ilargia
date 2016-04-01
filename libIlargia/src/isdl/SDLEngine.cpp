#include <memory>
#include <anax/anax.hpp>
#include "isdl/SDLEngine.h"

namespace Ilargia {

    void SDLEngine::configure(std::vector<std::string>& args) {
        int imgFlags = IMG_INIT_PNG;
        if (SDL_Init(SDL_INIT_EVERYTHING) >= 0 ) {
            TTF_Init();
            _window = WindowPtr(SDL_CreateWindow("Testing Ilargia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    640, 480, SDL_WINDOW_SHOWN));

            SDL_Renderer* _renderer;
            if (_window) {
                _renderer = SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);
                            }
        } else {
            Engine::shutdownEngine(1);
        }

    }

    void SDLEngine::initSystems() {
        _world = std::unique_ptr<anax::World>(new anax::World());
        /*for(auto& systemPtr: _systems) {
            _world->addSystem(dynamic_cast<anax::System>(systemPtr));
        }*/
    }

    void SDLEngine::processInput() {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    Engine::shutdownEngine(0);
                    break;
                default:
                    break;
            }
        }

    }

    void SDLEngine::update(float deltaTime) {
        _world->refresh();

    }

    void SDLEngine::render() {
        //_renderingSystem.render();
    }

    void SDLEngine::shutdown() {
        _window.reset(); //SDL_DestroyWindow(iWindow);
        _world->removeSystem<RenderSystem>();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }


}

