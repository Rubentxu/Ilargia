#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H

#include <string>
#include <memory>
#include <set>
#include "Node.h"
#include "Context.h"

namespace bt {
    struct Node;
    struct Context;
    enum class Status;
    using NodePtr = std::unique_ptr<Node>;

    std::string generateUUID();

    struct BehaviorTree {
        std::string _id;
        std::string _title;
        std::string _description;
        NodePtr _root;

        BehaviorTree(NodePtr root) : BehaviorTree(std::move(root), "The behavior tree","Default description"){}

        BehaviorTree(NodePtr root, std::string title, std::string desc);

        Status tick(Context &context);

    };


};
#endif //ILARGIA_BEHAVIORTREE_H
