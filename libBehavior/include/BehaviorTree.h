#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H

#include <string>
#include <memory>
#include "Node.h"
#include "Context.h"
#include "BlackBoard.h"

namespace bt {
    using TargetPtr = std::shared_ptr<boost::any>;
    using ContextPtr = std::unique_ptr<Context>;
    using BlackBoardPtr = std::shared_ptr<BlackBoard>;

    std::string generateUUID();

    enum class Status {
        SUCCESS, FAILURE, RUNNING, ERROR
    };

    class BehaviorTree : std::enable_shared_from_this<BehaviorTree> {
        std::string _id;
        std::string _title;
        std::string _description;
        bt::NodePtr _root;
        ContextPtr _context;
    public:
        BehaviorTree(NodePtr root, std::string title = "The behavior tree", std::string desc = "Default description");

        Status tick(TargetPtr &target, BlackBoardPtr &blackBoard);

        std::string getId() const {
            return _id;
        }

    };


};
#endif //ILARGIA_BEHAVIORTREE_H
