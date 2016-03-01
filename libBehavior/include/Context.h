#ifndef ILARGIA_CONTEXT_H
#define ILARGIA_CONTEXT_H

#include "Global.h"
#include <set>

namespace bt {

    struct Context {
        BehaviorTree    &_behavior;
        TargetPtr       _target;
        BlackBoard      &_blackBoard;

        Context() = delete;

        Context(BehaviorTree &behavior, TargetPtr &target, BlackBoard &blackBoard) = delete;

        Context(const Context&) =  delete;

        Context& operator=(const Context&) = delete;

    };

};
#endif //ILARGIA_CONTEXT_H
