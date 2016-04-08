#include "isdl/Systems/RenderSystem.h"


namespace Ilargia {


    void RenderSystem::draw(ViewComponent &view) {
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = view.bounds.w;
        srcRect.h = view.bounds.h;
        SDL2pp::Texture& texture = _assetManager->getAsset<SDL2pp::Texture>(view.textureId);
/*
        SDL_SetTextureAlphaMod(texture, view.color.a);
        SDL_SetTextureColorMod(texture, view.color.r, view.color.g, view.color.b);
        SDL_RenderCopyEx(renderer, texture, &srcRect, &view.bounds, view.rotation, &view.center, view.flip);*/
    }

    void RenderSystem::render() {
        auto entities = getEntities();
        SDL_Renderer *renderer = _renderer.get()->Get();
        _renderer->SetDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
        _renderer->Clear();
        for (auto &entity : entities) {
            // TODO ordenar View por layer y renderizar por orden
            draw(entity.getComponent<ViewComponent>());
        }
        SDL_RenderPresent(renderer);
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

}