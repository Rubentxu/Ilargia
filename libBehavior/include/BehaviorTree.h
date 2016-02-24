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
#include "Node.h"

namespace bt {

    struct BehaviorTree {
        std::string _id;
        std::string _title;
        std::string _description;
        NodePtr _root;
    public:
        BehaviorTree() = delete;

        BehaviorTree(NodePtr root) : BehaviorTree(root, "The behavior tree","Default description"){}

        BehaviorTree(NodePtr root, std::string title, std::string desc);

        Status tick(ContextPtr &context);

    };


};
#endif //ILARGIA_BEHAVIORTREE_H
