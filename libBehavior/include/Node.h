#ifndef ILARGIA_NODE_H
#define ILARGIA_NODE_H

#include <string>
#include <map>
#include <boost/any.hpp>
#include <memory>
#include <chrono>
#include "Context.h"
#include "BehaviorTree.h"

//std::string operator "" _s(const char*, std::size_t);

namespace bt {

    enum class NodeCategorie {
        COMPOSITE, DECORATOR, ACTION, CONDITION
    };

    enum class Status {
        SUCCESS=0, FAILURE=1, RUNNING=2, ERROR=3, NONE=4
    };


    struct Node {
        std::string _id;
        std::string _name;
        NodeCategorie _category;
        std::string _description;

        Node(std::string name,NodeCategorie category,std::string description="Default description");

        virtual void open(Context &context) { }

        virtual void close(Context &context) { }

        virtual void enter(Context &context) { }

        virtual void exit(Context &context) { }

        virtual Status tick(Context &context) { }

        virtual Status execute(Context &context);

        virtual ~Node() = default;
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