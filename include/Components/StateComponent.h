#ifndef ILARGIA_STATECOMPONENT_H
#define ILARGIA_STATECOMPONENT_H

#include <anax/Component.hpp>
#include <string>

namespace Ilargia {

    struct StateComponent : anax::Component {
        float time = 0.0f;
        int oldState = -1;
        bool isChanged = false;
        std::vector<std::string> states;
        int typeIndex = -1;
        int currentState = 0;
    };
}



#endif //ILARGIA_STATECOMPONENT_H
