#include "SDLAssetManager.h"

namespace Ilargia {

    SDLAssetManager::SDLAssetManager(SDL_Renderer *renderer) : _renderer(renderer) {
        Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
    }

    SDLAssetManager::~SDLAssetManager() {
        Mix_CloseAudio();
    }

    bool SDLAssetManager::loadTexture(std::string fileName, std::string id) {
        SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

        if (pTempSurface == 0) {
            std::cout << IMG_GetError();
            return false;
        }

        SDL_Texture *pTexture = SDL_CreateTextureFromSurface(_renderer.get(), pTempSurface);
        SDL_FreeSurface(pTempSurface);

        if (pTexture != 0) {
            _textures[id] = TexturePtr(pTexture);
            return true;
        }
        return false;
    }

    bool SDLAssetManager::loadMusic(std::string fileName, std::string id) {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if (pMusic == 0) {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _musics[id] = pMusic;
        return true;

    }

    bool SDLAssetManager::loadSoundFx(std::string fileName, std::string id) {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if (pChunk == 0) {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        _sfxs[id] = pChunk;
        return true;
    }

    bool SDLAssetManager::loadFont(std::string fileName, std::string id, int size) {
        TTF_Font *gFont = TTF_OpenFont(fileName.c_str(), size);

        if (gFont == 0) {
            std::cout << TTF_GetError();
            return false;
        }
        _fonts[id] = FontPtr(gFont);
        return true;

    }




}
