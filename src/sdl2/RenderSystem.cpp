#include "RenderSystem.h"


namespace Ilargia {

    RenderSystem::RenderSystem(SDL_Renderer *renderer) : _renderer(renderer) { }

    void RenderSystem::draw(ViewComponent &view) {
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = view.w;
        srcRect.h = view.h;
        SDL_SetTextureAlphaMod(view.texture, view.opacity);
        SDL_RenderCopyEx(_renderer.get(), view.texture, &srcRect, &view, view.rotation, &view.center, view.flip);
    }

    /*void RenderSystem::drawFrame(SDL_Texture *texture, int x, int y, int width, int height, int currentRow, int currentFrame,
                                   double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        SDL_Rect srcRect;
        SDL_Rect destRect;
        srcRect.x = width * currentFrame;
        srcRect.y = height * currentRow;
        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;
        destRect.x = x;
        destRect.y = y;


        SDL_RenderCopyEx(_renderer.get(), texture, &srcRect, &destRect, angle, 0, flip);
    }

    void RenderSystem::drawTile(SDL_Texture *texture, int margin, int spacing, int x, int y, int width, int height,
                                   int currentRow, int currentFrame)  {
        SDL_Rect srcRect;
        SDL_Rect destRect;
        srcRect.x = margin + (spacing + width) * currentFrame;
        srcRect.y = margin + (spacing + height) * currentRow;
        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;
        destRect.x = x;
        destRect.y = y;

        SDL_RenderCopyEx(_renderer.get(), texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
    }*/

    void RenderSystem::render() {
        auto entities = getEntities();
        for (auto &entity : entities) {
            draw(entity.getComponent<ViewComponent>());
        }
        SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(_renderer.get());
        SDL_RenderPresent(_renderer.get());
    }

    RendererPtr &RenderSystem::getRenderer() {
       // assert(!isValid() && "Render system is not valid");
        return _renderer;
    }

    bool RenderSystem::isValid() const {
        return _renderer == nullptr;
    }
}