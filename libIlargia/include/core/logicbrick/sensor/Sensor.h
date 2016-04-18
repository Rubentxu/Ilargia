#ifndef ILARGIA_SENSOR_H
#define ILARGIA_SENSOR_H

#include <core/logicbrick/LogicBrick.h>
#include "mathfu/vector.h">

namespace Ilargia {

    enum class Pulse { PM_IDLE, PM_TRUE, PM_FALSE, PM_BOTH };
    enum class TapMode { TAP_OUT, TAP_IN };

    struct Sensor : LogicBrick {
        // Config Values
        float frequency = 0;
        bool invert = false;
        bool tap = false;
        Pulse pulse = Pulse::PM_IDLE; // Valorar si quitar. Duplicidad de funcionalidad con positive

        // Values
        float tick = 0;
        bool positive = false;
        bool firstExec = true;
        bool initialized = false;
        TapMode firstTap = TapMode::TAP_IN;
        TapMode lastTap = TapMode::TAP_OUT;

    };

    enum class MouseEvent {
        MOUSEMOTION = 0x400, MOUSEBUTTONDOWN, MOUSEBUTTONUP, MOUSEWHEEL
    };

    template <typename Entity>
    struct MouseSensor : Sensor {
        MouseEvent mouseEvent = MouseEvent::MOUSEMOTION;
        Entity target;

        MouseEvent mouseEventSignal;
        mathfu::Vector<float, 2> positionSignal;
        int amountScrollSignal;

    };
}

#endif //ILARGIA_SENSOR_H
