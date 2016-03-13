#include "TextureManager.h"
#include "SDL_image.h"
#include "SDL.h"
namespace Ilargia {

    bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer) {
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




    void TextureManager::clearTextureMap() {
        m_textureMap.clear();
    }

    void TextureManager::clearFromTextureMap(std::string id) {
        m_textureMap.erase(id);
    }


}
