#ifndef ILARGIA_STATESYSTEM_H
#define ILARGIA_STATESYSTEM_H

#include <anax/anax.hpp>
#include "Components/StateComponent.h"

namespace Ilargia {
    class StateSystem : public anax::System<anax::Requires <StateComponent>> {
    public:
        void update(float deltaTime);
    };
}


#endif //ILARGIA_STATESYSTEM_H
