#ifndef ILARGIA_CONTROLLER_H
#define ILARGIA_CONTROLLER_H

#include <memory>
#include <unordered_map>
#include "core/Sensor.h"
#include "core/Actuator.h"
#include "LogicBrick.h"

namespace Ilargia {

    class Controller : LogicBrick {
        std::unordered_map<std::string,std::unique_ptr<Sensor>> sensors;
        std::unordered_map<std::string,std::unique_ptr<Actuator>> actuators;

    };
}

#endif //ILARGIA_CONTROLLER_H
