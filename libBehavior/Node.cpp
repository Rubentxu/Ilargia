#include "Node.h"
using namespace bt;


Node::Node(std::string name,NodeCategorie category,std::string description): _name{name}, _category{category}, _description{description}{
    _id = generateUUID();
}


Status Node::execute(Context &context) {
    enter(context);
    bool &isOpen = context._blackBoard.getParam<bool>("isOpen", context._behavior._id, _id);
    if(!isOpen) {
        context._currentOpenNodes.insert(this);
        isOpen = true;
        open(context);
    }

    Status status = tick(context);

    if(status != Status::RUNNING) {
        context._currentOpenNodes.erase(this);
        isOpen = false;
        close(context);
    }

    exit(context);
    return status;
}