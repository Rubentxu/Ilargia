#ifndef ILARGIA_NODE_H
#define ILARGIA_NODE_H

#include <string>
#include <map>
#include <boost/any.hpp>
#include <memory>
#include <chrono>
#include "Context.h"
#include "BlackBoard.h"
#include "BehaviorTree.h"

//std::string operator "" _s(const char*, std::size_t);

namespace bt {

    enum class NodeCategorie {
        COMPOSITE, DECORATOR, ACTION, CONDITION
    };

    enum class Status {
        SUCCESS, FAILURE, RUNNING, ERROR
    };

    class Node : std::enable_shared_from_this<Node> {
    protected:
        std::string _id;
        std::string _name;
        NodeCategorie _category;
        std::string _description;

        void _open(ContextPtr &context);

        void _close(ContextPtr &context);

        void _enter(ContextPtr &context);

        void _exit(ContextPtr &context);

        Status _tick(ContextPtr &context);

    public:
        Node(){}

        Node(std::string name,NodeCategorie category);

        Node(std::string name,NodeCategorie category,std::string description);

        virtual std::string getId();

        virtual void open(ContextPtr &context) { };

        virtual void close(ContextPtr &context) { };

        virtual void enter(ContextPtr &context) { };

        virtual void exit(ContextPtr &context) { };

        virtual Status tick(ContextPtr &context) { };

        virtual Status execute(ContextPtr &context);

        virtual ~Node() { };
    };



    class Condition : public Node {
    public:
        Condition() : Node{"DefaultCondition", NodeCategorie::CONDITION }{}

        Condition(std::string name) : Node{name, NodeCategorie::CONDITION }{}

        Condition(std::string name, std::string description)
                : Node{name, NodeCategorie::CONDITION, description }{}

    };

};

#endif //ILARGIA_NODE_H
