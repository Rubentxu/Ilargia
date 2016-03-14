#include "AssetManager.h"
#include <SDL_image.h>

namespace Ilargia {

    bool AssetManager::loadTexture(std::string fileName, std::string id, SDL_Renderer *pRenderer) {
        SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

        if (pTempSurface == 0) {
            std::cout << IMG_GetError();
            return false;
        }

        SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        if (pTexture != 0) {
            m_textureMap[id] = pTexture;
            return true;
        }
        return false;
    }

    void AssetManager::clearTextureMap() {
        m_textureMap.clear();
    }

    void AssetManager::clearFromTextureMap(std::string id) {
        m_textureMap.erase(id);
    }


}
