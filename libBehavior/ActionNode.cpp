#include "ActionNode.h"

namespace bt {

    void Wait::_open(ContextPtr &context) {
        context->_blackBoard->setParam("startTime", std::chrono::system_clock::now(), context->_behavior.lock()->getId(),
                                       getId());
    }

    Status Wait::tick(ContextPtr &context) {
        auto currTime = std::chrono::system_clock::now();
        auto startTime = context->_blackBoard
                ->getParam<std::chrono::time_point<std::chrono::system_clock>>("startTime", context->_behavior.lock()->getId(),
                                                                                                            getId());

        if (currTime - startTime > _endTime) {
            return Status::SUCCESS;
        }

        return Status::RUNNING;
    };

}