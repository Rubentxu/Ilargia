#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
namespace Ilargia {

    class TextureManager {

        std::map<std::string, SDL_Texture *> m_textureMap;

    public:
        TextureManager() { }

        TextureManager(const TextureManager &) = delete;

        TextureManager &operator=(const TextureManager &) = delete;

        bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);

        void clearTextureMap();

        void clearFromTextureMap(std::string id);

        void draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer,
                  SDL_RendererFlip flip = SDL_FLIP_NONE);

        void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                       SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow,
                      int currentFrame, SDL_Renderer *pRenderer);

        std::map<std::string, SDL_Texture *> getTextureMap() { return m_textureMap; }


    };



#endif

}