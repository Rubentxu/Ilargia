#ifndef ILARGIA_STATE_H
#define ILARGIA_STATE_H

#include <string>

namespace Ilargia {

    struct State {
        float time = 0.0f;
        int oldState = -1;
        bool isChanged = false;
        std::vector<std::string> states;
        int typeIndex = -1;
        int currentState = 0;
    };
}



#endif //ILARGIA_STATE_H
