#include "ActionNode.h"

namespace bt {
    using namespace std::chrono;
    void Wait::open(Context &context) {
        context._blackBoard.setParam("startTime", std::chrono::high_resolution_clock::now(), context._behavior._id, _id);
    }

    Status Wait::tick(Context &context) {
        auto currTime = std::chrono::high_resolution_clock::now();
        auto startTime = context._blackBoard.getParam<std::chrono::system_clock::time_point>("startTime", context._behavior._id, _id);

        std::chrono::duration<double, std::milli> elapsed  = currTime-startTime;
        if (elapsed > _endTime) {
            return Status::SUCCESS;
        }

        return Status::RUNNING;
    };

}