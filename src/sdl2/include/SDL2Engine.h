#ifndef ILARGIA_SDL2ENGINE_H
#define ILARGIA_SDL2ENGINE_H

#include<SDL.h>
#include "Engine.h"

namespace Ilargia {

    class SDL2Engine : public Engine {
    public:
        SDL_Window *iWindow;
        SDL_Renderer *iRenderer;

        virtual void configure() override {
            // initialize SDL
            if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
                iWindow = SDL_CreateWindow("Testing Ilargia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           640, 480,SDL_WINDOW_SHOWN);
                if (iWindow != 0) {
                    iRenderer = SDL_CreateRenderer(iWindow, -1, 0);
                }
            }
            else {
                Engine::shutdown(1);
            }

        }


        template<typename T>
        virtual T *getSystem() = 0;

        virtual void initSystems() override { }

        virtual void processInput() override {
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

        virtual void update(float deltaTime) override { }

        virtual void render() override {
            SDL_SetRenderDrawColor(iRenderer, 0, 0, 0, 255);
            SDL_RenderClear(iRenderer);
            SDL_RenderPresent(iRenderer);
        }

        virtual void shutdown(int errorCode) override {
            Engine::shutdown(errorCode);
            SDL_DestroyWindow(iWindow);
            SDL_DestroyRenderer(iRenderer);
            SDL_Quit();
        }

    };

}


#endif //ILARGIA_SDL2ENGINE_H
