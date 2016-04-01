#ifndef ILARGIA_VIEW_ACTUATOR_H
#define ILARGIA_VIEW_ACTUATOR_H

#include <core/Actuator.h>
#include "Components/ViewComponent.h"

namespace Ilargia {
    struct ViewActuator : Actuator<ViewComponent>  { };
}

#endif //ILARGIA_VIEW_ACTUATOR_H
