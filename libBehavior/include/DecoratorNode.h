#ifndef ILARGIA_DECORATORNODE_H
#define ILARGIA_DECORATORNODE_H

#include "Node.h"

namespace bt {
    class Decorator : public Node {
    protected:
        NodePtr _child;
    public:

        Decorator(NodePtr child) : Node{"DefaultDecorator",NodeCategorie::DECORATOR}, _child{child} {}

        Decorator(std::string name,NodePtr child) : Node{name,NodeCategorie::DECORATOR}, _child{child} {}


    };

    class Inverter : virtual public Decorator {
    public:

        Inverter(NodePtr child) : Decorator{"DefaultInverter",child} {}

        Inverter(std::string name,NodePtr child) : Decorator{name,child} {}

        Status tick(ContextPtr &context) override ;

    };

    class Limiter : virtual public Decorator {
        int _maxLoop = 1;
    public:

        Limiter(NodePtr child, int maxLoop) : Decorator{"DefaultLimiter",child}, _maxLoop{maxLoop} {}

        Limiter(std::string name,NodePtr child, int maxLoop) : Decorator{name,child}, _maxLoop{maxLoop} {}

        void open(ContextPtr &context) override;

        Status tick(ContextPtr &context) override ;

    };
}
#endif //ILARGIA_DECORATORNODE_H
