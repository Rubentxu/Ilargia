#ifndef ILARGIA_CONTEXT_H
#define ILARGIA_CONTEXT_H

#include "BehaviorTree.h"
#include "BlackBoard.h"
#include <set>

namespace bt {
    struct BehaviorTree;
    using TargetPtr = std::shared_ptr<boost::any>;

    struct Context {
        BehaviorTree    &_behavior;
        TargetPtr       _target;
        BlackBoard      &_blackBoard;

        Context(BehaviorTree &behavior, BlackBoard &blackBoard) : _behavior(behavior), _blackBoard(blackBoard) { }

    };

};
#endif //ILARGIA_CONTEXT_H
