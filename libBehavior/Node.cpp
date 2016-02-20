#include "Node.h"
using namespace bt;

void Node::_open(ContextPtr &context) {
    context->_openNodes.insert(shared_from_this());
    context->_blackBoard->setParam("isOpen", true, context->_behavior->getId(),_id);
    open(context);
}

void Node::_close(ContextPtr &context) {
    context->closeNode(shared_from_this());
    context->_blackBoard->setParam("isOpen", false, context->_behavior->getId(),_id);
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

    if(context->_blackBoard->getParam<bool>("isOpen", context->_behavior->getId(), getId())) {
        open(context);
    }

    Status status = _tick(context);

    if(status != Status::RUNNING) {
        _close(context);
    }

    _exit(context);
    return status;
}

void Wait::_open(ContextPtr &context){
    context->_blackBoard->setParam("startTime", std::chrono::system_clock::now(), context->_behavior->getId(), getId());
}

Status Wait::tick(ContextPtr &context) {
    auto currTime = std::chrono::system_clock::now();
    auto startTime = context->_blackBoard->getParam<std::chrono::time_point<std::chrono::system_clock>>("startTime", context->_behavior->getId(), getId());

    if (currTime - startTime > _endTime) {
        return Status::SUCCESS;
    }

    return Status::RUNNING;
};

Status Sequence::tick(ContextPtr& context) {

    for (auto child: _children) {
        Status status = child->execute(context);

        if (status != Status::SUCCESS) {
            return status;
        }
    }

    return Status::SUCCESS;
}
