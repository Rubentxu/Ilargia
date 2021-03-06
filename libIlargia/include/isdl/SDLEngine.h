#ifndef ILARGIA_SDLEngine_H
#define ILARGIA_SDLEngine_H

#include <memory>
#include <type_traits>
#include <vector>
#include "core/Manager.h"
#include "Systems/RenderSystem.h"
#include "core/Engine.h"

namespace Ilargia {


    class SDLEngine : public Engine {
    private:
        std::unique_ptr<anax::World> _world;
        SDL2pp::Window _window;

    public:

        SDLEngine() = default;

        virtual void configure(std::vector<std::string>& args) override ;

        virtual void initSystems() override ;

        virtual void processInput() override ;

        virtual void update(float deltaTime) override ;

        virtual void render() override ;

        virtual void shutdown() override ;


        anax::World& getWorld() {
            return *_world;
        }
        


    };
}
#endif // ILARGIA_SDLEngine_H
