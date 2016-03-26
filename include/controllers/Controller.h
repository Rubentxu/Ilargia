#include <LogicBrick.h>
#include <unordered_map>
#include <sensors/Sensor.h>
#include <bits/unique_ptr.h>

#ifndef ILARGIA_CONTROLLER_H
#define ILARGIA_CONTROLLER_H

namespace Ilargia {


    class Controller : LogicBrick {
        std::unordered_map<std::string,std::unique_ptr<Sensor>> sensors;
        std::unordered_map<std::string,std::unique_ptr<Sensor>> actuators;


    };
}

#endif //ILARGIA_CONTROLLER_H
