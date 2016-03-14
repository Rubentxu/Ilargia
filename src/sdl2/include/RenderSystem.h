#ifndef ILARGIA_RENDERSYSTEM_H
#define ILARGIA_RENDERSYSTEM_H

#include <anax/anax.hpp>
#include "Util.h"
#include "Components/ViewComponent.h"
#include "AssetManager.h"

namespace Ilargia {
    class RenderSystem : public anax::System<anax::Requires<ViewComponent>> {
        std::shared_ptr<AssetManager> _assetManager;

        void draw(ViewComponent &view, SDL_Renderer* renderer);

      /*  void drawFrame(SDL_Texture *texture, int x, int y, int width, int height, int currentRow, int currentFrame,
                       double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void drawTile(SDL_Texture *texture, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);*/

    public:
        RenderSystem() = default;

        RenderSystem(std::shared_ptr<AssetManager> assetManager);

        void render();

        RendererPtr& getRenderer();

        bool isValid() const;

    };
}

#endif //ILARGIA_RENDERSYSTEM_H
