#ifndef __SDLAssetManager__
#define __SDLAssetManager__

#include <iostream>
#include "SDLUtil.h"
#include "core/AssetManager.h"

namespace Ilargia {
    class Texture: public AssetMap<SDL_Texture>{
    public:
        bool loadAsset(std::string fileName, std::string id, SDL_Renderer* renderer);

    };

    class Music: public AssetMap<Mix_Music>{
    public:
        bool loadAsset(std::string fileName, std::string id);

    };

    class SoundFX: public AssetMap<Mix_Chunk>{
    public:
        bool loadAsset(std::string fileName, std::string id);

    };

    class TFont: public AssetMap<TTF_Font>{
    public:
        bool loadAsset(std::string fileName, std::string id, int size);

    };

    class SDLAssetManager : public AssetManager<Texture, Music, SoundFX, TFont> {
    public:
        SDLAssetManager();
        
        ~SDLAssetManager();

    };
}
#endif