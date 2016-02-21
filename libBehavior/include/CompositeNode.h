#ifndef ILARGIA_COMPOSITENODE_H
#define ILARGIA_COMPOSITENODE_H

#include "Node.h"

namespace bt {
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
}


#endif //ILARGIA_COMPOSITENODE_H
