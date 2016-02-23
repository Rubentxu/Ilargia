#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "NodeTest.h"


using namespace bt;

//using ::testing::Return;
template <Status T>
using TriggerPtr = std::shared_ptr<Trigger<T>>;
BehaviorTreePtr behavior;
ContextPtr context;

NodeTest::NodeTest() {
    behavior = std::make_shared<BehaviorTree>(std::make_shared<Trigger<Status::SUCCESS>>("name")) ;
    context = ContextPtr{new Context{behavior}};
};

NodeTest::~NodeTest() { };

void NodeTest::SetUp() {};

void NodeTest::TearDown() { };



TEST_F(NodeTest, triggerAction) {
    EXPECT_EQ(Status::SUCCESS,behavior->_root->tick(context));
}



