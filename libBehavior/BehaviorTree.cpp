#include "BehaviorTree.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

using namespace bt;


std::string bt::generateUUID() {
    static boost::uuids::random_generator gen;
    auto id = gen();
    return boost::lexical_cast<std::string>(id);
}

BehaviorTree::BehaviorTree(NodePtr root, std::string title, std::string desc)
        : _title{title}, _description{desc}, _root{std::move(root)}{
    _id = generateUUID();
}

Status BehaviorTree::tick(Context &context) {

    Status status = _root->execute(context);

    for(Node *node : _lastOpenNodes) {
        if(_currentOpenNodes.find(node) ==_currentOpenNodes.end()) node->close(context);
    }
    _lastOpenNodes = _currentOpenNodes;
    _currentOpenNodes.clear();

    return status;
}
