#include "BehaviorTree.h"

BehaviorTree::BehaviorTree(std::string title, std::string desc) {
    _title = title;
    _description = desc;
    _blackboard = std::unique_ptr<BlackBoard>();
}