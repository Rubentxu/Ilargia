#ifndef ILARGIA_CONTEXT_H
#define ILARGIA_CONTEXT_H

#include "Global.h"
#include <set>

namespace bt {

    struct Context {
        BehaviorTreePtr _behavior;
        TargetPtr _target;
        BlackBoardPtr _blackBoard;
        std::set<NodePtr> _openNodes;

        Context() = default;

        void enterNode(NodePtr node);

        void exitNode(NodePtr node);

        void openNode(NodePtr node);

        void closeNode(NodePtr node);

        void tickNode(NodePtr node);

        /*void &BlackBoard getContextMemory() {
            return this.getExtendMemory(this.Id, this.ContextId)
        }*/

    };


};
#endif //ILARGIA_CONTEXT_H
