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

    template<Status enabled, Status disabled>
    class Toggle : public Action {
        Status currentStatus = disabled;

    public:
        Toggle(std::string name="DefaultToggle"): Action(name) {}

        Status tick(Context &context) override {
            if(currentStatus== enabled) {
                currentStatus = disabled;
            } else {
                currentStatus = enabled;
            }
            return currentStatus;
        };

    };

    template<Status enabled, Status disabled>
    class LimiterAndToggle : public Action {
        int _maxLoop = 1;
        struct CurrentStatus{
            Status status = enabled;
            int count = 0;
        };

    public:
        LimiterAndToggle(int maxLoop): Action("DefaultLimiterAndToggle"), _maxLoop{maxLoop} {}

        LimiterAndToggle(std::string name, int maxLoop): Action(name), _maxLoop{maxLoop} {}


        Status tick(Context &context) override {
            CurrentStatus &currentStatus = context._blackBoard.getParam<CurrentStatus>("currentStatus", context._behavior._id, _id);
            if (currentStatus.count >= _maxLoop) {
                if(currentStatus.status== enabled) {
                    currentStatus.status = disabled;
                } else {
                    currentStatus.status = enabled;
                }
                currentStatus.count = 0;
            }
            currentStatus.count++;

            return currentStatus.status;
        };

    };

}
#endif //ILARGIA_ACTIONNODE_H
