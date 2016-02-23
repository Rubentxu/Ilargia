#ifndef ILARGIA_ACTIONNODE_H
#define ILARGIA_ACTIONNODE_H

#include <chrono>
#include "Node.h"

namespace bt {

    class Action : public Node {
    public:

        Action(std::string name) : Node(name,NodeCategorie::ACTION) {}

    };

    template<Status status>
    class Trigger : public Action {
    public:
        Trigger(): Action("DefaultTrigger") {}

        Trigger(std::string name): Action(name) {}

        Status tick(ContextPtr &context) {
            return status;
        };
    };

    class Wait : public Action {
        std::chrono::duration<int, std::milli> _endTime;
    public:
        Wait(int milliseconds): Action("DefaultWait"), _endTime{milliseconds}{
            _name = "Wait";
        }

        void _open(ContextPtr &context);

        Status tick(ContextPtr &context);
    };

}
#endif //ILARGIA_ACTIONNODE_H
