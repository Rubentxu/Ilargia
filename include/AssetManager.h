#ifndef __AssetManager__
#define __AssetManager__

#include <iostream>
#include <string>
#include <map>
#include <SDL.h>
#include "SDLUtil.h"

namespace Ilargia {

    class AssetManager {
        RendererPtr _renderer;
        std::map<std::string, TexturePtr> m_textureMap;
        std::map<std::string, FontPtr> m_fontMap;
        std::map<std::string, Mix_Chunk*> m_sfxs;
        std::map<std::string, Mix_Music*> m_music;
    public:

        AssetManager(SDL_Renderer *renderer);

        AssetManager(const AssetManager &) = delete;

        AssetManager &operator=(const AssetManager &) = delete;
        
        ~AssetManager();

        virtual bool loadTexture(std::string fileName, std::string id);

        bool loadMusic(std::string fileName, std::string id);

        bool loadSoundFx(std::string fileName, std::string id);

        bool loadFont(std::string fileName, std::string id, int size);

        virtual void clearTextureMap();

        virtual void clearFromTextureMap(std::string id);

        SDL_Texture* getTexture(std::string id) {
            return m_textureMap[id].get();
        }
        
        TTF_Font* getFont(std::string id) {
            return m_fontMap[id].get();
        }
        
        Mix_Music* getMusic(std::string id) {
            return m_music[id];
        }
        
        Mix_Chunk* getSoundFX(std::string id) {
            return m_sfxs[id];
        }

        RendererPtr& getRenderer() {
            return _renderer;
        }

    };
}
#endif