#ifndef ILARGIA_MOUSESENSOR_H
#define ILARGIA_MOUSESENSOR_H

#include <SDL_events.h>
#include <anax/Entity.hpp>
#include "Sensor.h"

namespace Ilargia {
    enum class MouseEvent {
        MOUSEMOTION = 0x400, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSEWHEEL
    };

    struct MouseSensor : public Sensor {
        MouseEvent mouseEvent = MouseEvent::MOUSEMOTION;
        anax::Entity target;



    };
}

#endif //ILARGIA_MOUSESENSOR_H
