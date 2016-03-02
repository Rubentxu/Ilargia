#ifndef ILARGIA_DECORATORNODE_H
#define ILARGIA_DECORATORNODE_H

#include "Node.h"

namespace bt {
    class Decorator : public Node {
    protected:
        NodePtr _child;
    public:

        Decorator(NodePtr &child) : Node{"DefaultDecorator",NodeCategorie::DECORATOR} {
            _child = std::move(child);
        }

        Decorator(std::string name,NodePtr &child) : Node{name,NodeCategorie::DECORATOR}, _child{std::move(child)} {}

    };

    class Inverter : public Decorator {
    public:

        Inverter(NodePtr child) : Decorator{"DefaultInverter",child} {}

        Inverter(std::string name,NodePtr child) : Decorator{name,child} {}

        Status tick(Context &context) override ;

    };

    class Limiter : public Decorator {
        int _maxLoop = 1;
    public:

        Limiter(NodePtr child, int maxLoop) : Decorator{"DefaultLimiter",child}, _maxLoop{maxLoop} {}

        Limiter(std::string name,NodePtr child, int maxLoop) : Decorator{name,child}, _maxLoop{maxLoop} {}

        void open(Context &context) override;

        Status tick(Context &context) override ;

    };

    class MaxTime : public Decorator {
        std::chrono::duration<double, std::milli> _maxTime;
        Status currentStatus = Status::NONE;
    public:

        MaxTime(NodePtr child, double maxTime) : Decorator{"DefaultMaxTime",child}, _maxTime{maxTime} {}

        MaxTime(std::string name,NodePtr child, double maxTime) : Decorator{name,child}, _maxTime{maxTime} {}

        void open(Context &context) override;

        Status tick(Context &context) override ;

    };

    class Repeater : public Decorator {
        int _maxLoop = 1;
    public:

        Repeater(NodePtr child, int maxLoop) : Decorator{"DefaultRepeater",child}, _maxLoop{maxLoop} {}

        Repeater(std::string name,NodePtr child, int maxLoop) : Decorator{name,child}, _maxLoop{maxLoop} {}

        void open(Context &context) override;

        Status tick(Context &context) override ;

    };
}
#endif //ILARGIA_DECORATORNODE_H
