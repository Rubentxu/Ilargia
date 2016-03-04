#include "CompositeNode.h"

namespace bt {
    Status Sequence::tick(Context &context) {
        for (auto &child: _children) {
            Status status = child->execute(context);

            if (status != Status::SUCCESS) {
                return status;
            }
        }
        return Status::SUCCESS;
    }

    Status MemSequence::tick(Context &context) {
        std::size_t &indexChild = context._blackBoard.getParam<std::size_t>("indexRunningChild", context._behavior._id,_id);
        for (std::size_t i = indexChild; i < _children.size();i++) {
            Status status = _children[i]->execute(context);

            if (status != Status::SUCCESS) {
                if(status == Status::RUNNING) {
                    indexChild= i;
                }
                return status;
            }
        }
        return Status::SUCCESS;
    }

    void MemSequence::close(Context &context) {
        context._blackBoard.setParam<std::size_t>("indexRunningChild", 0,context._behavior._id,_id);
    }


    Status Priority::tick(Context &context) {
        for (auto &child: _children) {
            Status status = child->execute(context);

            if (status != Status::FAILURE) {
                return status;
            }
        }
        return Status::FAILURE;
    }

    Status MemPriority::tick(Context &context) {
        std::size_t &indexChild = context._blackBoard.getParam<std::size_t>("indexRunningChild", context._behavior._id,_id);
        for (std::size_t i = indexChild; i < _children.size();i++) {
            Status status = _children[i]->execute(context);

            if (status != Status::FAILURE) {
                if(status == Status::RUNNING) {
                    indexChild= i;
                }
                return status;
            }
        }
        return Status::FAILURE;
    }

    void MemPriority::close(Context &context) {
        context._blackBoard.setParam<std::size_t>("indexRunningChild", 0,context._behavior._id,_id);
    }

}