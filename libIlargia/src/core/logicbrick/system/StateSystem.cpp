#include "core/logicbrick/system/StateSystem.h"
#include "core/logicbrick/Components.h"

namespace Ilargia {

    void StateSystem::process(State &state, float deltaTime) {
        state.time += deltaTime;

        if (state.currentState == -1) {

        }
        if (state.oldState != state.currentState) {
            state.oldState = state.currentState;
            state.isChanged = true;

        } else {
            state.isChanged = false;
        }
    }
}