#ifndef ILARGIA_SENSORCOMPONENT_H
#define ILARGIA_SENSORCOMPONENT_H

#include <vector>
#include "core/sensor/Sensor.h"

namespace Ilargia {

    struct DefaultBase {};

    template<typename Sensor, typename BaseComponent = DefaultBase>
    struct SensorComponents : BaseComponent {
        std::vector<std::vector<Sensor>> sensors;
    };


    struct MouseSensorComponents : SensorComponents<MouseSensor> { };

}

#endif //ILARGIA_SENSORCOMPONENT_H
