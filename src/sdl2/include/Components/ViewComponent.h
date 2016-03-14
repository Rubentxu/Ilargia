#ifndef ILARGIA_TEXTURECOMPONENT_H
#define ILARGIA_TEXTURECOMPONENT_H

#include "SDL.h"
#include <SDL_rect.h>
#include <anax/Component.hpp>

namespace Ilargia {

    struct ViewComponent : anax::Component, public SDL_Rect {
        std::string textureId;
        double rotation = 0;
        Uint8 opacity = 1;
        int layer;
        SDL_Point center;
        SDL_Color color;
        SDL_RendererFlip flip = SDL_FLIP_NONE;

    };

}
#endif //ILARGIA_TEXTURECOMPONENT_H
