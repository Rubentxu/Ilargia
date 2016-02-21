#ifndef ILARGIA_ACTIONNODE_H
#define ILARGIA_ACTIONNODE_H

#include <chrono>
#include "Node.h"

namespace bt {

    class Action : public Node {
    public:
        Action() {
            _category = NodeCategorie::ACTION;
        }

    };

    template<Status status>
    class Trigger : public Action {
    public:

        Status tick(ContextPtr &context) {
            return status;
        };
    };

    class Wait : public Action {
        std::chrono::duration<double> _endTime;
    public:
        Wait(int milliseconds) {
            _name = "Wait";
        }

        void _open(ContextPtr &context);

        Status tick(ContextPtr &context);
    };

}
#endif //ILARGIA_ACTIONNODE_H
