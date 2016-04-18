#ifndef ILARGIA_ACTUATOR_H
#define ILARGIA_ACTUATOR_H

#include "core/logicbrick/LogicBrick.h"
#include <functional>

namespace Ilargia {

    struct Actuator : LogicBrick  {
        bool isActive = false;
    };

   /* struct TextureActuator: public Actuator {
     TextureView textureView;
     float height = 0;
     float width = 0;
     int opacity = -1;
     bool flipX;
     bool flipY;
     Color tint;
    };*/
}


#endif //ILARGIA_ACTUATOR_H
