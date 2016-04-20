#ifndef ILARGIA_ENGINE_STATESYSTEM_H
#define ILARGIA_ENGINE_STATESYSTEM_H

#include "core/logicbrick/Components.h"

namespace Ilargia {
    class IStateSystem {
    protected:
        virtual void process(State &state, float deltaTime) = 0;
    };

    class StateSystem: public IStateSystem {
    protected:
        virtual void process(State &state, float deltaTime);

    };
}
#endif //ILARGIA_ENGINE_STATESYSTEM_H
