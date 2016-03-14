#ifndef __AssetManager__
#define __AssetManager__

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include "Util.h"

namespace Ilargia {

    class AssetManager {
        RendererPtr _renderer;
        std::map<std::string, SDL_Texture*> m_textureMap;
    public:
        AssetManager(SDL_Renderer *renderer) : _renderer(renderer) { }

        AssetManager(const AssetManager &) = delete;

        AssetManager &operator=(const AssetManager &) = delete;

        virtual bool loadTexture(std::string fileName, std::string id, SDL_Renderer *pRenderer);

        virtual void clearTextureMap();

        virtual void clearFromTextureMap(std::string id);

        std::map<std::string, SDL_Texture *> getTextureMap() { return m_textureMap; }

        RendererPtr& getRenderer() { return _renderer; }

    };
}
#endif