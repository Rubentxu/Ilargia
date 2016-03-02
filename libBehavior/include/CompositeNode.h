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

        std::vector<NodePtr> _children;

    public:

        Composite(std::string name, std::initializer_list<Node*> nodes)
                : Node{name,NodeCategorie::COMPOSITE}  {

            for ( auto &it : nodes ) {
                _children.push_back( NodePtr(it) );

            }
        }

      /*  Composite(std::initializer_list<Node> &nodes)
                : Composite{"DefaultDecorator",nodes} {}*/

        Composite(const Composite&) = delete;

        Composite& operator=(const Composite&) = delete;

        ~Composite() = default;

    };

    class Sequence : public Composite {
    public:
        Sequence(std::initializer_list<Node*> &ini) : Composite::Composite{"Sequence",ini} {};

        Status tick(Context &context) override;
    };
}
#endif //ILARGIA_COMPOSITENODE_H
