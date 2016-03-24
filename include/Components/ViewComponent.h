#ifndef ILARGIA_TEXTURECOMPONENT_H
#define ILARGIA_TEXTURECOMPONENT_H

#include "SDL.h"
#include <SDL_rect.h>
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
#endif //ILARGIA_TEXTURECOMPONENT_H
