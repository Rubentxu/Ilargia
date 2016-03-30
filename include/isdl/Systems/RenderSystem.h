#ifndef ILARGIA_RenderSystem_H
#define ILARGIA_RenderSystem_H

#include "SDLUtil.h"
#include "Components/ViewComponent.h"
#include "core/AssetsManager.h"
#include <anax/anax.hpp>

namespace Ilargia {
    class RenderSystem: public anax::System<anax::Requires<ViewComponent>> {

        void draw(ViewComponent &view, SDL_Renderer* renderer);

      /*  void drawFrame(SDL_Texture *texture, int x, int y, int width, int height, int currentRow, int currentFrame,
                       double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void drawTile(SDL_Texture *texture, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);*/

    public:

        RenderSystem(std::shared_ptr<AssetsManager> assetManager) :RenderSystem{assetManager} {};

        ~RenderSystem();



        virtual void render(SDLAssetManager& assetManager);

        virtual bool isValid() const;

    };
}

#endif //ILARGIA_RenderSystem_H
