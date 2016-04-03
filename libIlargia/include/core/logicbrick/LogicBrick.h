#ifndef ILARGIA_LOGICBRICK_H
#define ILARGIA_LOGICBRICK_H

#include <string>

namespace Ilargia {

    enum class BrickMode { BM_IDLE, BM_ON, BM_OFF };

    struct LogicBrick {
        std::string name;
        int state = -1;
        BrickMode pulseState = BrickMode::BM_IDLE;

    };

}

#endif //ILARGIA_LOGICBRICK_H
