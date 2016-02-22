#include "Node.h"
using namespace bt;


Node::Node(std::string name,NodeCategorie category) : _name{name}, _category{category}, _id{ bt::generateUUID()} {};

Node::Node(std::string name,NodeCategorie category,std::string description): Node{name, category} { _description = description; };


void Node::_open(ContextPtr &context) {
    context->_openNodes.insert(shared_from_this());
    context->_blackBoard->setParam("isOpen", true, context->_behavior.lock()->getId(),_id);
    open(context);
}

void Node::_close(ContextPtr &context) {
    context->closeNode(shared_from_this());
    context->_blackBoard->setParam("isOpen", false, context->_behavior.lock()->getId(),_id);
    close(context);
}

void Node::_enter(ContextPtr &context) {
    context->enterNode(shared_from_this());
    enter(context);
}

void Node::_exit(ContextPtr &context) {
    context->exitNode(shared_from_this());
    exit(context);
}

Status Node::_tick(ContextPtr &context) {
    context->tickNode(shared_from_this());
    return tick(context);
}


Status Node::execute(ContextPtr &context) {
    enter(context);

    if(context->_blackBoard->getParam<bool>("isOpen", context->_behavior.lock()->getId(), getId())) {
        open(context);
    }

    Status status = _tick(context);

    if(status != Status::RUNNING) {
        _close(context);
    }

    _exit(context);
    return status;
}