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
            _map[id] = std::unique_ptr<SDL_Texture> (pTexture);
            return true;
        }
        return false;

    }

    void Texture::Free_Functor::operator() (SDL_Texture* ptr) {
        SDL_DestroyTexture(ptr);
        ptr = nullptr;
    }



    bool Music::loadAsset(std::string fileName, std::string id) {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if (pMusic == 0) {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _map[id] = std::unique_ptr<Mix_Music,Free_Functor> (pMusic);
        return true;
    }

    void Music::destroy(Mix_Music* ptr) {
        Mix_FreeMusic(ptr);
        ptr = nullptr;
    }

    bool SoundFX::loadAsset(std::string fileName, std::string id)  {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if (pChunk == 0) {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _map[id] = std::unique_ptr<Mix_Chunk,Free_Functor> (pChunk);
        return true;
    }

    void SoundFX::destroy(Mix_Chunk* ptr) {
        Mix_FreeChunk(ptr);
        ptr = nullptr;
    }

    bool TFont::loadAsset(std::string fileName, std::string id, int size)  {
        TTF_Font *gFont = TTF_OpenFont(fileName.c_str(), size);

        if (gFont == 0) {
            std::cout << TTF_GetError();
            return false;
        }
        _map[id] = std::unique_ptr<TTF_Font,Free_Functor> (gFont);
        return true;
    }

    void TFont::destroy(TTF_Font* ptr) {
        TTF_CloseFont(ptr);
        ptr = nullptr;
    }

}
