#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include <Node.h>
#include <ActionNode.h>

using namespace bt;
class NodeTest : public ::testing::Test {

protected:

    virtual ~NodeTest();

    virtual void SetUp();

    virtual void TearDown();

public:
    NodePtr node;
    ContextPtr context;
};
