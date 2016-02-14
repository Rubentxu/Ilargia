#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H

#include <string>
#include <memory>
#include "Node.h"
#include "BlackBoard.h"

enum class Status { SUCCESS, FAILURE, RUNNING, ERROR};
class Node;

class BehaviorTree {
    std::string                 _id;
    std::string                 _title;
    std::string                 _description;
    std::shared_ptr<Node>       _root;
    std::unique_ptr<BlackBoard> _blackboard;
public:
    BehaviorTree(std::string title, std::string desc);

};


#endif //ILARGIA_BEHAVIORTREE_H
