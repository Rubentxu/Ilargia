#include "BehaviorTree.h"
#include <algorithm>

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

Status BehaviorTree::tick(ContextPtr &context) {
    context->_openNodes.clear();

    Status status = _root->execute(context);
    auto lastOpenNodes = context->_blackBoard->getParam<std::set<NodePtr>>("openNodes", _id);

    for(NodePtr node : lastOpenNodes) {
        if(context->_openNodes.find(node)== context->_openNodes.end()) node->_close(context);
    }
    context->_blackBoard->setParam("openNodes", context->_openNodes, _id);

    return status;
}
