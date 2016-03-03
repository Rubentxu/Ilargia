#ifndef ILARGIA_COMPOSITENODE_H
#define ILARGIA_COMPOSITENODE_H

#include "Node.h"
#include <vector>
#include <iterator>
#include <initializer_list>

namespace bt {
    class Composite : public Node {
    protected:
        std::vector<NodePtr> _children;

    public:

        Composite(std::string name, std::initializer_list<Node*> nodes)
                : Node{name,NodeCategorie::COMPOSITE}  {
            for ( auto &it : nodes ) {
                _children.push_back( NodePtr(it) );

            }
        }

    };

    class Sequence : public Composite {
    public:
        Sequence(std::initializer_list<Node*> &&nodes) : Composite::Composite{"Sequence",nodes} {};

        Status tick(Context &context) override;
    };
}
#endif //ILARGIA_COMPOSITENODE_H
