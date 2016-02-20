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
#include "Context.h"


//std::string operator "" _s(const char*, std::size_t);

namespace bt {

    enum class Status;
    class Context;
    using ContextPtr = std::unique_ptr<Context>;

    std::string generateUUID();

    enum class NodeCategorie {
        COMPOSITE, DECORATOR, ACTION, CONDITION
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

        Node() : _name{"Default"} { _id = generateUUID(); };

        Node(std::string name) : _name{name} { _id = generateUUID(); };

        virtual std::string getId();

        virtual void open(ContextPtr &context) { };

        virtual void close(ContextPtr &context) { };

        virtual void enter(ContextPtr &context) { };

        virtual void exit(ContextPtr &context) { };

        virtual Status tick(ContextPtr &context) { };

        virtual Status execute(ContextPtr &context);

        virtual ~Node() { };
    };

    using NodePtr = std::shared_ptr<Node>;

    class Condition : public Node {
    public:
        Condition() {
            _category = NodeCategorie::CONDITION;
        }

    };

    class Decorator : public Node {
    public:
        NodePtr _child;

        Decorator(NodePtr child) : _child{child} {
            _category = NodeCategorie::DECORATOR;
        }

    };

    class Action : public Node {
    public:
        Action() {
            _category = NodeCategorie::ACTION;
        }

    };


    class Composite : public Node {
    protected:
        std::vector<NodePtr> _children;
    public:
        Composite(std::initializer_list<NodePtr> &ini) : _children{ini} {
            _category = NodeCategorie::COMPOSITE;
        }

        virtual Status tick(ContextPtr &context) { };
    };

    class Sequence : public Composite {
    public:
        Sequence(std::initializer_list<NodePtr> &ini) : Composite::Composite{ini} {
            _name = "Sequence";
        };

        Status tick(ContextPtr &context) override;
    };

};

#endif //ILARGIA_NODE_H
