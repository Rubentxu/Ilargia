#ifndef ILARGIA_NODE_H
#define ILARGIA_NODE_H

#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <memory>
#include "BehaviorTree.h"

struct Context;
using ContextPtr = std::unique_ptr<Context>;

enum class NodeCategorie {
    COMPOSITE, DECORATOR, ACTION, CONDITION
};

class Context;
enum class Status;
class BehaviorTree;
std::string generateUUID();

class Node {
    std::string _id;
    std::string _name;
    NodeCategorie _category;
    std::string _description;

public:

    Node() : _name{"Default"} { _id = generateUUID(); };

    Node(std::string name) : _name{name} { _id = generateUUID(); };

    virtual std::string getId();

    virtual void enter(ContextPtr& context);

    virtual void exit(ContextPtr& context);

    virtual void open(ContextPtr& context);

    virtual void close(ContextPtr& context);

    virtual Status tick(ContextPtr& context);

    virtual Status execute(ContextPtr& context);

    virtual ~Node();
};

#endif //ILARGIA_NODE_H
