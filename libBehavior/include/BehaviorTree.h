#ifndef ILARGIA_BEHAVIORTREE_H
#define ILARGIA_BEHAVIORTREE_H

#include <string>
#include <memory>
#include "Node.h"
#include "BlackBoard.h"


std::string generateUUID() {
    static boost::uuids::random_generator gen;
    auto id = gen();
    return boost::lexical_cast<std::string>(id);
}

enum class Status {
    SUCCESS, FAILURE, RUNNING, ERROR
};

class Node;
class BehaviorTree;

using TargetPtr = std::shared_ptr<boost::any>;
using NodePtr = std::shared_ptr<Node>;
using BehaviorTreePtr = std::shared_ptr<BehaviorTree>;
using BlackBoardPtr = std::shared_ptr<BlackBoard>;

struct Context {
    std::shared_ptr<BehaviorTree> _behavior;
    TargetPtr _target;
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

class BehaviorTree : std::enable_shared_from_this<BehaviorTree>{
    std::string _id;
    std::string _title;
    std::string _description;
    NodePtr _root;
    ContextPtr _context;
public:
    BehaviorTree(NodePtr root, std::string title = "The behavior tree", std::string desc = "Default description");

    Status tick(TargetPtr& target, BlackBoardPtr& blackBoard);

    std::string getId() const {
        return _id;
    }

};


#endif //ILARGIA_BEHAVIORTREE_H
