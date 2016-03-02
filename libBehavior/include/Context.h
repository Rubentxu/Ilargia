#ifndef ILARGIA_CONTEXT_H
#define ILARGIA_CONTEXT_H

#include "Global.h"
#include <set>

namespace bt {

    struct Context {
        BehaviorTree    &_behavior;
        TargetPtr       _target;
        BlackBoard      &_blackBoard;

        Context(BehaviorTree &behavior, BlackBoard &blackBoard) : _behavior(behavior), _blackBoard(blackBoard) { }

    };

};
#endif //ILARGIA_CONTEXT_H
