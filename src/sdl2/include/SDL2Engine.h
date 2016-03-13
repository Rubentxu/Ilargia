#ifndef ILARGIA_SDL2ENGINE_H
#define ILARGIA_SDL2ENGINE_H

#include "Util.h"
#include "Engine.h"
#include "TextureManager.h"
#include "RenderSystem.h"

namespace Ilargia {

    class SDL2Engine : public Engine {
    public:
        WindowPtr _window;
        std::unique_ptr<anax::World> world;

        virtual void configure() override;

        virtual void initSystems() override { }

        virtual void processInput() override;

        virtual void update(float deltaTime) override { }

        virtual void render() override {

        }

        virtual void shutdown(int errorCode) override;

    };

}


#endif //ILARGIA_SDL2ENGINE_H
