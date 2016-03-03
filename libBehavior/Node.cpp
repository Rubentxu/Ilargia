#include "Node.h"
using namespace bt;


Node::Node(std::string name,NodeCategorie category,std::string description): _name{name}, _category{category}, _description{description}{
    _id = generateUUID();
}


Status Node::execute(Context &context) {
    enter(context);

    if(!context._blackBoard.getParam<bool>("isOpen", context._behavior._id, _id)) {
        context._currentOpenNodes.insert(this);
        context._blackBoard.setParam("isOpen", true, context._behavior._id, _id);
        open(context);
    }

    Status status = tick(context);

    if(status != Status::RUNNING) {
        context._currentOpenNodes.erase(this);
        context._blackBoard.setParam("isOpen", false, context._behavior._id, _id);
        close(context);
    }

    exit(context);
    return status;
}