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

enum class Status;
class BehaviorTree;
std::string generateUUID();

class Node  : std::enable_shared_from_this<BehaviorTree> {
protected:
    std::string _id;
    std::string _name;
    NodeCategorie _category;
    std::string _description;

    void _open(ContextPtr& context);

    void _close(ContextPtr& context);

    void _enter(ContextPtr& context);

    void _exit(ContextPtr& context);

    Status _tick(ContextPtr& context);


public:

    Node() : _name{"Default"} { _id = generateUUID(); };

    Node(std::string name) : _name{name} { _id = generateUUID(); };

    virtual std::string getId();

    virtual void open(ContextPtr& context);

    virtual void close(ContextPtr& context);

    virtual void enter(ContextPtr& context);

    virtual void exit(ContextPtr& context);

    virtual Status tick(ContextPtr& context);

    virtual Status execute(ContextPtr& context);

    virtual ~Node();
};

template<size_t rows>
class Composite : public Node {
    std::array<NodePtr, rows>  _children;
public:
    //Composite(const std::initialier_list<NodePtr>& children) : _children {I()...}, _category{NodeCategorie::COMPOSITE} {}
    template <typename... Types>
    Composite(NodePtr t, Types... ts) : _children{ { t, ts... } } {}
};



#endif //ILARGIA_NODE_H
