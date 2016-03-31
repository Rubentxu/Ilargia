#ifndef ILARGIA_SENSORCOMPONENT_H
#define ILARGIA_SENSORCOMPONENT_H

#include <anax/Component.hpp>
#include <vector>
#include "isdl/sensors/MouseSensor.h"

namespace Ilargia {

    template<typename Sensor>
    struct SensorComponents : anax::Component {
        std::vector<std::vector<Sensor>> sensors;
    };

    struct MouseSensorComponents : SensorComponents<MouseSensor> { };

}

#endif //ILARGIA_SENSORCOMPONENT_H
