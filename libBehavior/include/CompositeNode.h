#ifndef ILARGIA_COMPOSITENODE_H
#define ILARGIA_COMPOSITENODE_H

#include "Node.h"

namespace bt {
    class Composite : public Node {
    protected:
        std::vector<NodePtr> _children;
    public:
        Composite(std::string name, std::initializer_list<NodePtr> &ini)
                : Node{name,NodeCategorie::COMPOSITE}, _children{ini} {}

        Composite(std::initializer_list<NodePtr> &ini)
                : Node{"DefaultDecorator",NodeCategorie::COMPOSITE}, _children{ini} {}

    };

    class Sequence : public Composite {
    public:
        Sequence(std::initializer_list<NodePtr> &ini) : Composite::Composite{"Sequence",ini} {};

        Status tick(ContextPtr &context) override;
    };
}
#endif //ILARGIA_COMPOSITENODE_H
