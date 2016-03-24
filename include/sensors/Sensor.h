#ifndef ILARGIA_SENSOR_H
#define ILARGIA_SENSOR_H

#include <LogicBrick.h>

namespace Ilargia {
    struct Sensor : public LogicBrick {
        float frequency = 0;
        bool invert = false;

    };
}

#endif //ILARGIA_SENSOR_H
