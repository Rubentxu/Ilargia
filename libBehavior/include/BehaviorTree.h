#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H



enum class Status { SUCCESS, FAILURE, RUNNING, ERROR};
enum class NodeCategorie { COMPOSITE, DECORATOR, ACTION, CONDITION };

class BehaviorTree {

      std::string _id;
    std::string _title;
    std::string _description;
    std::__shared_ptr<Node> _root;
    std::__shared_ptr<BlackBoard> _blackboard;

};


#endif //ILARGIA_BEHAVIORTREE_H
