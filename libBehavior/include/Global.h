#ifndef ILARGIA_GLOBAL_H
#define ILARGIA_GLOBAL_H

#include <memory>
#include <string>
#include <boost/any.hpp>

namespace bt {
    enum class Status;
    class Context;
    using ContextPtr = std::unique_ptr<Context>;
    class BehaviorTree;
    using BehaviorTreePtr = std::shared_ptr<BehaviorTree>;
    using BehaviorTreeWPtr = std::weak_ptr<BehaviorTree>;
    using TargetPtr = std::shared_ptr<boost::any>;
    class BlackBoard;
    using BlackBoardPtr = std::shared_ptr<BlackBoard>;
    class Node;
    using NodePtr = std::shared_ptr<Node>;
    std::string generateUUID();
}
#endif //ILARGIA_GLOBAL_H