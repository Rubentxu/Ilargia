#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "NodeTest.h"
#include "BehaviorTree.h"
#include <memory>

using namespace bt;

//using ::testing::Return;
template <Status T>
using TriggerPtr = std::shared_ptr<Trigger<T>>;

NodeTest::~NodeTest() { };

void NodeTest::SetUp() {
    auto action = new Trigger<Status::SUCCESS>();
    auto nodep = std::shared_ptr<Trigger<Status::SUCCESS>>{std::move(action)};
    auto behavior = std::make_shared<BehaviorTree>() ;
    context = ContextPtr{new Context{behavior}};
    context->_blackBoard = BlackBoardPtr{};
};

void NodeTest::TearDown() { };


/*
TEST_F(NodeTest, triggerAction) {
    node = TriggerPtr<Status::SUCCESS>{};
    EXPECT_EQ(Status::SUCCESS,node->tick(context));
}
*/


