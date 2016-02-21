#include "CompositeNode.h"

namespace bt {
    Status Sequence::tick(ContextPtr& context) {

        for (auto child: _children) {
            Status status = child->execute(context);

            if (status != Status::SUCCESS) {
                return status;
            }
        }

        return Status::SUCCESS;
    }
}