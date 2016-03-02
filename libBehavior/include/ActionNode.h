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

        Trigger(std::string name="DefaultTrigger"): Action(name) {}

        Status tick(Context &context) override {
            return status;
        };
    };

    class Wait : public Action {
        std::chrono::duration<double, std::milli> _endTime;

    public:
        Wait(double milliseconds, std::string name="DefaultWait"): Action(name), _endTime{milliseconds}{}

        void open(Context &context) override ;

        Status tick(Context &context) override ;
    };

}
#endif //ILARGIA_ACTIONNODE_H
