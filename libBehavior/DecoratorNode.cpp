#include "DecoratorNode.h"

namespace bt {
    Status Inverter::tick(ContextPtr &context) {
        if (!_child) {
            return Status::ERROR;
        }

        Status status = _child->execute(context);

        if (status == Status::SUCCESS) {
            status = Status::FAILURE;
        } else if (status == Status::FAILURE) {
            status = Status::SUCCESS;
        }
        return status;

    }

    void Limiter::open(ContextPtr &context) {
        context->_blackBoard->setParam("count", 0, context->_behavior->_id, getId());
    }

    Status Limiter::tick(ContextPtr &context) {
        if (!_child) {
            return Status::ERROR;
        }

        int count = context->_blackBoard->getParam<int>("count", context->_behavior->_id, getId());

        if (count < _maxLoop) {
            Status status = _child->execute(context);

            if (status == Status::SUCCESS || status == Status::FAILURE)
                context->_blackBoard->setParam("count", count+1, context->_behavior->_id, getId());

            return status;
        }
        return Status::FAILURE;

    }
}