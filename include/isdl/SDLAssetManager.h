#ifndef __SDLAssetManager__
#define __SDLAssetManager__

#include <iostream>
#include "SDLUtil.h"
#include "core/AssetsManager.h"

namespace Ilargia {
    class Texture: public AssetMap<SDL_Texture>{
        RendererPtr _renderer;
    public:
        virtual bool loadAsset(std::string fileName, std::string id) override {
            SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

            if (pTempSurface == 0) {
                std::cout << IMG_GetError();
                return false;
            }

            SDL_Texture *pTexture = SDL_CreateTextureFromSurface(_renderer.get(), pTempSurface);
            SDL_FreeSurface(pTempSurface);

            if (pTexture != 0) {
                auto pair = std::make_pair<std::string,AssetPtr>(std::move(id),AssetPtr (pTexture));
                _map.insert(pair);
                return true;
            }
            return false;
        }

        virtual void destroy(SDL_Texture* ptr) override { SDL_DestroyTexture(ptr); }
    };

    class SDLAssetManager : public AssetsManager<Texture> {
    public:
        SDLAssetManager();
        
        ~SDLAssetManager();

    };
}
#endif