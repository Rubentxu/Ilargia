#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H

#include <string>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include "Global.h"
#include "Context.h"

namespace bt {


    struct BehaviorTree : std::enable_shared_from_this<BehaviorTree> {
        std::string _id;
        std::string _title;
        std::string _description;
        NodePtr _root;
        ContextPtr _context;
    public:
        BehaviorTree(NodePtr root) : BehaviorTree(root, "The behavior tree","Default description"){}

        BehaviorTree(NodePtr root, std::string title, std::string desc);

        Status tick(TargetPtr &target, BlackBoardPtr &blackBoard);

        std::string getId() const {
            return _id;
        }

    };


};
#endif //ILARGIA_BEHAVIORTREE_H
