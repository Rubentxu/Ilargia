#ifndef ILARGIA_ACTUATOR_H
#define ILARGIA_ACTUATOR_H

#include "core/logicbrick/LogicBrick.h"
#include <functional>

namespace Ilargia {
    template <class... Components>
    struct Actuator : LogicBrick  {
        std::function<void (Components...)> actuator;
    };
}


#endif //ILARGIA_ACTUATOR_H
