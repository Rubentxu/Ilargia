#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include <thread>
#include "NodeTest.h"


using namespace bt;

//using ::testing::Return;
template <Status T>
using TriggerPtr = std::shared_ptr<Trigger<T>>;

BehaviorTree behavior;
BlackBoard blackBoard;
Context *context;

NodeTest::NodeTest() {
    behavior = BehaviorTree{NodePtr(new Trigger<Status::SUCCESS> {"name"})};
    blackBoard = BlackBoard{};
    context = new Context{behavior,blackBoard};
    context->_target = std::make_shared<boost::any>(1);
};

NodeTest::~NodeTest() { };

void NodeTest::SetUp() {};

void NodeTest::TearDown() { };


// Testing Action Nodes
TEST_F(NodeTest, triggerActionSuccess) {
    EXPECT_EQ(Status::SUCCESS,behavior._root->execute(*context));
}


TEST_F(NodeTest, triggerActionFailure) {
    behavior._root = NodePtr(new Trigger<Status::FAILURE> {"name"});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
}

TEST_F(NodeTest, triggerActionError) {
    behavior._root = NodePtr(new Trigger<Status::ERROR>{"name"});
    EXPECT_EQ(Status::ERROR, behavior._root->execute(*context));
}

TEST_F(NodeTest, triggerActionRunning) {
    behavior._root = NodePtr(new Trigger<Status::RUNNING>{"name"});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
}

TEST_F(NodeTest, actionWait) {
    behavior._root = NodePtr(new Wait{50.0});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    std::this_thread::sleep_for( std::chrono::duration<double, std::milli>{80.0});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));

}


// Testing Decorator Nodes
TEST_F(NodeTest, decoratorInverterFailure) {
    behavior._root = NodePtr(new Inverter {NodePtr(new Trigger<Status::SUCCESS>{"name"})});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
}

TEST_F(NodeTest, decoratorInverterSucces) {
    behavior._root = NodePtr(new Inverter {NodePtr(new Trigger<Status::FAILURE>{"name"})});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
}


TEST_F(NodeTest, decoratorInverterError) {
    behavior._root = NodePtr(new Inverter {nullptr});
    EXPECT_EQ(Status::ERROR, behavior._root->execute(*context));
}


TEST_F(NodeTest, decoratorLimiter) {
    behavior._root = NodePtr(new Limiter{NodePtr(new Trigger<Status::SUCCESS>{"name"}),2});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
}
