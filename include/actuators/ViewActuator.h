#ifndef ILARGIA_ACTUATOR_H
#define ILARGIA_ACTUATOR_H

#include <LogicBrick.h>
#include <functional>
#include "Components/ViewComponent.h"

namespace Ilargia {
    struct ViewActuator : LogicBrick  {
        std::function<void (ViewComponent)> actuator;
    };
}

#endif //ILARGIA_ACTUATOR_H
