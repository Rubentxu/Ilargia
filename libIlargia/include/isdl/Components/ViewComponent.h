#ifndef ILARGIA_VIEWCOMPONENT_H
#define ILARGIA_VIEWCOMPONENT_H

#include <SDL2pp/SDL2pp.hh>
#include <string>
#include <anax/Component.hpp>

namespace Ilargia {

    struct ViewComponent : anax::Component {
        std::string textureId;
        SDL_Rect bounds;
        double rotation = 0;
        int layer=1;
        SDL_Point center;
        SDL_Color color = {255,255,255,255};
        SDL_RendererFlip flip = SDL_FLIP_NONE;

    };

}
#endif //ILARGIA_VIEWCOMPONENT_H
