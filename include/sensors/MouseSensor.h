#ifndef ILARGIA_MOUSESENSOR_H
#define ILARGIA_MOUSESENSOR_H

#include <SDL_events.h>
#include <anax/Entity.hpp>
#include <"mathfu/vector.h">
#include "Sensor.h"

namespace Ilargia {
    enum class MouseEvent {
        MOUSEMOTION = 0x400, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSEWHEEL
    };

    struct MouseSensor : public Sensor {
        MouseEvent mouseEvent = MouseEvent::MOUSEMOTION;
        anax::Entity target;

        MouseEvent mouseEventSignal;
        mathfu::vec2 positionSignal;
        int amountScrollSignal;

    };
}

#endif //ILARGIA_MOUSESENSOR_H
