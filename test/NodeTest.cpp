#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "NodeTest.h"


using namespace bt;

//using ::testing::Return;
template <Status T>
using TriggerPtr = std::shared_ptr<Trigger<T>>;
std::shared_ptr<BehaviorTree> behavior;
ContextPtr context;

NodeTest::NodeTest() {
    behavior = std::make_shared<BehaviorTree>(std::make_shared<Trigger<Status::SUCCESS>>("name"));
    context = ContextPtr(new Context{});
    context->_behavior = behavior ;
    context->_target = std::make_shared<boost::any>(1);
    context->_blackBoard = std::make_shared<BlackBoard>();
};

NodeTest::~NodeTest() { };

void NodeTest::SetUp() {};

void NodeTest::TearDown() { };



TEST_F(NodeTest, triggerActionSuccess) {
    EXPECT_EQ(Status::SUCCESS,behavior->_root->tick(context));
}


TEST_F(NodeTest, triggerActionFailure) {
    behavior->_root = std::make_shared<Trigger<Status::FAILURE>>("name");
    EXPECT_EQ(Status::FAILURE,behavior->_root->tick(context));
}

TEST_F(NodeTest, triggerActionError) {
    behavior->_root = std::make_shared<Trigger<Status::ERROR>>("name");
    EXPECT_EQ(Status::ERROR,behavior->_root->tick(context));
}

TEST_F(NodeTest, triggerActionRunning) {
    behavior->_root = std::make_shared<Trigger<Status::RUNNING>>("name");
    EXPECT_EQ(Status::RUNNING,behavior->_root->tick(context));
}

TEST_F(NodeTest, triggerActionWait) {
    behavior->_root = std::make_shared<Wait>(2);
    //behavior->_root->_open();
    EXPECT_EQ(Status::RUNNING,behavior->_root->tick(context));
}
