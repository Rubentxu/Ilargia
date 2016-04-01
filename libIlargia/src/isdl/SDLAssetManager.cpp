#include "isdl/SDLAssetManager.h"

namespace Ilargia {

    bool Texture::loadAsset(std::string fileName, std::string id, SDL_Renderer* renderer) {
        SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

        if (pTempSurface == 0) {
            std::cout << IMG_GetError();
            return false;
        }

        SDL_Texture *pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);

        if (pTexture != 0) {
            _map[id] = TexturePtr(pTexture);
            return true;
        }
        return false;

    }


    bool Music::loadAsset(std::string fileName, std::string id) {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if (pMusic == 0) {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _map[id] = MusicPtr(pMusic);
        return true;
    }


    bool SoundFX::loadAsset(std::string fileName, std::string id)  {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if (pChunk == 0) {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _map[id] = SoundFXPtr(pChunk);
        return true;
    }

    bool TFont::loadAsset(std::string fileName, std::string id, int size)  {
        TTF_Font *gFont = TTF_OpenFont(fileName.c_str(), size);

        if (gFont == 0) {
            std::cout << TTF_GetError();
            return false;
        }
        _map[id] = FontPtr(gFont);
        return true;
    }

}
