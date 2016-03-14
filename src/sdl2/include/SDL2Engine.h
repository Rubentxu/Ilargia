#ifndef ILARGIA_SDL2ENGINE_H
#define ILARGIA_SDL2ENGINE_H

#include "Util.h"
#include "Engine.h"
#include "RenderSystem.h"

namespace Ilargia {

    class SDL2Engine : public Engine {
        WindowPtr _window;
        std::shared_ptr<AssetManager> _assetManager;
    public:

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
