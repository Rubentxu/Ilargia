#ifndef __SDLAssetManager__
#define __SDLAssetManager__

#include <iostream>
#include "SDLUtil.h"
#include "core/Manager.h"

namespace Ilargia {
    class Texture: public AssetMap<TexturePtr>{
    public:
        bool loadAsset(std::string fileName, std::string id, SDL_Renderer* renderer);
        void destroy(SDL_Texture* ptr);
    };

    class Music: public AssetMap<MusicPtr>{
    public:
        bool loadAsset(std::string fileName, std::string id);
    };

    class SoundFX: public AssetMap<SoundFXPtr>{
    public:
        bool loadAsset(std::string fileName, std::string id);
    };

    class TFont: public AssetMap<FontPtr>{
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