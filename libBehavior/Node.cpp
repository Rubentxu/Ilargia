#include "Node.h"
using namespace bt;


Node::Node(std::string name,NodeCategorie category,std::string description): _name{name}, _category{category}, _description{description}{
    _id = generateUUID();
}


Status Node::execute(Context &context) {
    enter(context);

    if(context._behavior._currentOpenNodes.find(this) == context._behavior._currentOpenNodes.end()) {
        context._behavior._currentOpenNodes.insert(this);
        open(context);
    }

    Status status = tick(context);

    if(status != Status::RUNNING) {
        context._behavior._currentOpenNodes.erase(this);
        close(context);
    }

    exit(context);
    return status;
}