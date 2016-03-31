#ifndef ILARGIA_RenderSystem_H
#define ILARGIA_RenderSystem_H

#include "isdl/SDLUtil.h"
#include "isdl/Components/ViewComponent.h"
#include "isdl/SDLAssetManager.h"
#include <anax/anax.hpp>

namespace Ilargia {
    class RenderSystem: public anax::System<anax::Requires<ViewComponent>> {
        std::shared_ptr<SDLAssetManager> _assetManager;
        RendererShPtr _renderer;

        void draw(ViewComponent &view, SDL_Renderer* renderer);

      /*  void drawFrame(SDL_Texture *texture, int x, int y, int width, int height, int currentRow, int currentFrame,
                       double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void drawTile(SDL_Texture *texture, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);*/

    public:

        RenderSystem(std::shared_ptr<SDLAssetManager> assetManager, RendererShPtr _renderer)
                :_assetManager(std::move(assetManager)),_renderer(std::move(_renderer)){};

        ~RenderSystem();

        virtual void render();

        virtual bool isValid() const;

    };
}

#endif //ILARGIA_RenderSystem_H
