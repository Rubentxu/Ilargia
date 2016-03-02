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

    struct Node {
        std::string _id;
        std::string _name;
        NodeCategorie _category;
        std::string _description;

        Node(){}

        Node(std::string name,NodeCategorie category);

        Node(std::string name,NodeCategorie category,std::string description);

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
