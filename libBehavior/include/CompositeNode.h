#ifndef ILARGIA_COMPOSITENODE_H
#define ILARGIA_COMPOSITENODE_H

#include "Node.h"
#include <vector>
#include <iterator>
#include <initializer_list>

namespace bt {
    class Composite : public Node {
    protected:
        struct ChildrenDeleter
        {
            void operator() (Node* node) const
            {
                delete node;
            }
        };

        std::vector<std::unique_ptr<Node,ChildrenDeleter>> _children;

    public:
        Composite(std::string name, std::initializer_list<NodePtr> nodes)
                : Node{name,NodeCategorie::COMPOSITE}  {

           /* _children {std::make_move_iterator(std::begin(nodes)),
                      std::make_move_iterator(std::end(nodes))};*/
        }

        Composite(std::initializer_list<NodePtr> &ini)
                : Composite{"DefaultDecorator",ini} {}

        Composite(const Composite&) = delete;

        Composite& operator=(const Composite&) = delete;

        ~Composite() = default;

    };

    class Sequence : public Composite {
    public:
        Sequence(std::initializer_list<NodePtr> &ini) : Composite::Composite{"Sequence",ini} {};

        Status tick(Context &context) override;
    };
}
#endif //ILARGIA_COMPOSITENODE_H
