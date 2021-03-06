#include "DecoratorNode.h"

namespace bt {

    Status Inverter::tick(Context &context) {
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

    void Limiter::open(Context &context) {
        context._blackBoard.setParam("count", 0, context._behavior._id, _id);
    }

    Status Limiter::tick(Context &context) {
        if (!_child) {
            return Status::ERROR;
        }

        int &count = context._blackBoard.getParam<int>("count", context._behavior._id, _id);

        if (count < _maxLoop) {
            Status status = _child->execute(context);

            if (status == Status::SUCCESS || status == Status::FAILURE){
                count++;
            }
            return Status::RUNNING ;
        }
        return Status::FAILURE;

    }

    using namespace std::chrono;
    Status MaxTime::tick(Context &context) {
        auto currTime = std::chrono::high_resolution_clock::now();
        MaxTimeState &state = context._blackBoard.getParam<MaxTimeState>("maxTimeContext", context._behavior._id, _id);

        state.currentStatus = _child->execute(context);
        std::chrono::duration<double, std::milli> elapsed  = currTime-state.startTime;
        if (elapsed > _maxTime) {
            return Status::FAILURE;
        }
        return state.currentStatus;
    }


    void Repeater::open(Context &context) {
        context._blackBoard.setParam("count", 0, context._behavior._id, _id);
    }

    Status Repeater::tick(Context &context) {
        if (!_child) {
            return Status::ERROR;
        }

        int &count = context._blackBoard.getParam<int>("count", context._behavior._id, _id);
        Status status = Status::SUCCESS;

        while (_maxLoop < 0 || count < _maxLoop) {
            status = _child->execute(context);

            if (status == Status::SUCCESS || status == Status::FAILURE){
                count++;
            } else {
                break;
            }
        }
        return status;

    }


    void RepeaterUntil::open(Context &context) {
        context._blackBoard.setParam("count", 0, context._behavior._id, _id);
    }

    Status RepeaterUntil::tick(Context &context) {
        if (!_child) {
            return Status::ERROR;
        }

        int &count = context._blackBoard.getParam<int>("count", context._behavior._id, _id);
        Status status = Status::ERROR;

        while (_maxLoop < 0 || count < _maxLoop) {
            status = _child->execute(context);

            if (status != _repeaterUntil ){
                count++;
            } else {
                break;
            }
        }
        return status;

    }

}