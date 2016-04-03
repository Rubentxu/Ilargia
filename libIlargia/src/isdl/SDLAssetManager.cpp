#include "isdl/SDLAssetManager.h"
#include <unordered_map>

namespace Ilargia {

    bool ILTexture::loadAsset(std::string fileName, std::string id) {        
        _map.insert(std::make_pair<std::string,SDL2pp::Texture>(std::move(id), SDL2pp::Texture(*_renderer,fileName)));
        return true;
    }


    bool ILMusic::loadAsset(std::string fileName, std::string id) {
        _map.insert(std::make_pair<std::string,SDL2pp::Music>(std::move(id), SDL2pp::Music(fileName)));
        return true;
    }


    bool ILSoundFX::loadAsset(std::string fileName, std::string id) {
        _map.insert(std::make_pair<std::string,SDL2pp::Chunk>(std::move(id), SDL2pp::Chunk(fileName)));
        return true;
    }

    bool ILFont::loadAsset(std::string fileName, std::string id, int size) {
        _map.insert(std::make_pair<std::string,SDL2pp::Font>(std::move(id), SDL2pp::Font(fileName, size)));
        return true;
    }

}
