#ifndef ILARGIA_NODE_H
#define ILARGIA_NODE_H

#include <string>
#include <bits/unique_ptr.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include "BehaviorTree.h"

class Context;

std::string generateUUID() {
    static boost::uuids::random_generator gen;
    auto id = gen();
    return boost::lexical_cast<std::string>(id);
}

class Node {
    std::string _id;
    std::string _name;
    std::unique_ptr<NodeCategorie> _category;
    std::string _title;
    std::string _description;

public:

    Node(std::string name) : _name{name}{
        _id = generateUUID();
    };

    virtual std::string getId();

    virtual void enter(Context &context);

    virtual void exit(Context &context);

    virtual void open(Context &context);

    virtual void close(Context &context);

    virtual Status tick(Context &context);
};

/*
Status ExecuteNode(Node &node, Context &context) {
    nodeMemory := context.get(node)
    context.enterNode(node);
    node.enter(context);

    if _, ok := nodeMemory.Bool["isOpen"];
    !ok {
            context.openNode(node);
            nodeMemory.Bool["isOpen"] =  true
            node.Open(context)

    }

    context.contextNode(node)
    status := node.Tick(context)

    if
        status != RUNNING {
                context.closeNode(node)
                nodeMemory.Bool["isOpen"]= false
                node.Close(context)
        }

    context.exitNode(node)
    node.Exit(context)

    return status
};*/


#endif //ILARGIA_NODE_H
