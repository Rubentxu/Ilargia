#ifndef ILARGIA_CONTEXT_H
#define ILARGIA_CONTEXT_H

#include "BehaviorTree.h"
#include "BlackBoard.h"


namespace bt {
    class BehaviorTree;
    using BehaviorTreePtr = std::shared_ptr<BehaviorTree>;
    using TargetPtr = std::shared_ptr<boost::any>;
    class BlackBoard;
    using BlackBoardPtr = std::shared_ptr<BlackBoard>;
    class Node;
    using NodePtr = std::shared_ptr<Node>;

    struct Context {
        BehaviorTreePtr _behavior;
        bt::TargetPtr _target;
        BlackBoardPtr _blackBoard;
        std::set<NodePtr> _openNodes;
        int _nodeCount = 0;

        Context(std::shared_ptr<BehaviorTree> behavior) : _behavior{behavior} { }

        void enterNode(NodePtr node);

        void exitNode(NodePtr node);

        void openNode(NodePtr node);

        void closeNode(NodePtr node);

        void tickNode(NodePtr node);

        /*void &BlackBoard getContextMemory() {
            return this.getExtendMemory(this.Id, this.ContextId)
        }*/

    };

    using ContextPtr = std::unique_ptr<Context>;

};
#endif //ILARGIA_CONTEXT_H
