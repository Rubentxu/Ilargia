#ifndef ILARGIA_DECORATORNODE_H
#define ILARGIA_DECORATORNODE_H

#include "Node.h"

namespace bt {
    class Decorator : public Node {
    public:
        NodePtr _child;

        Decorator(NodePtr child) : _child{child} {
            _category = NodeCategorie::DECORATOR;
        }

    };
}
#endif //ILARGIA_DECORATORNODE_H
