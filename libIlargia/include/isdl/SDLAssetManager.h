#ifndef __SDLAssetManager__
#define __SDLAssetManager__

#include "core/Manager.h"
#include <SDL2pp/SDL2pp.hh>

namespace Ilargia {
    class ILTexture: public AssetMap<SDL2pp::Texture>{
    protected:
        std::shared_ptr<SDL2pp::Renderer> _renderer;

    public:
        std::string baseDir;
        ILTexture(std::shared_ptr<SDL2pp::Renderer> renderer) : _renderer(renderer){}

        bool loadAsset(std::string fileName, std::string id);

    };

    class ILMusic: public AssetMap<SDL2pp::Music>{
    public:
        bool loadAsset(std::string fileName, std::string id);
    };

    class ILSoundFX: public AssetMap<SDL2pp::Chunk>{
    public:
        bool loadAsset(std::string fileName, std::string id);
    };

    class ILFont: public AssetMap<SDL2pp::Font>{
    public:
        bool loadAsset(std::string fileName, std::string id, int size);
    };

    class SDLAssetManager : public AssetManager<ILTexture, ILMusic, ILSoundFX, ILFont> {
    public:
        SDLAssetManager(std::shared_ptr<SDL2pp::Renderer> renderer) {
            _renderer = renderer;
        }
        
        ~SDLAssetManager();

    };
}
#endif