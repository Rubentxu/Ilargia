#ifndef ILARGIA_CONTROLLER_H
#define ILARGIA_CONTROLLER_H

#include <memory>
#include <unordered_map>
#include "core/logicbrick/sensor/Sensor.h"
#include "core/logicbrick/actuator/Actuator.h"
#include "core/logicbrick/LogicBrick.h"

namespace Ilargia {

    struct Controller : LogicBrick {
        std::unordered_map<std::string,std::unique_ptr<Sensor>> sensors;
        std::unordered_map<std::string,std::unique_ptr<Actuator>> actuators;
    };

    enum class Op {
        OP_NILL,
        OP_AND,
        OP_OR,
        OP_XOR,
        OP_NAND,
        OP_NOR,
        OP_XNOR,
    };

    struct ConditionalController : Controller {
     Op op;
     bool isInverter = false;
    };

    struct ScriptController : Controller {
        std::function<void(Controller)> script;
    };
}

#endif //ILARGIA_CONTROLLER_H
