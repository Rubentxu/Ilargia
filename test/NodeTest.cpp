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

BehaviorTree behavior{NodePtr(new Trigger<Status::SUCCESS> {"name"})};
BlackBoard blackBoard;
Context *context;

NodeTest::NodeTest() {
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

TEST_F(NodeTest, toggleAction) {
    behavior._root = NodePtr(new Toggle<Status::SUCCESS,Status::FAILURE>{"name"});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
}

TEST_F(NodeTest, limiterAndToggleAction) {
    behavior._root = NodePtr(new LimiterAndToggle<Status::SUCCESS,Status::FAILURE>{"name",2});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
}

TEST_F(NodeTest, actionWait) {
    behavior._root = NodePtr(new Wait{5.0});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    std::this_thread::sleep_for( std::chrono::duration<double, std::milli>{8.0});
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

TEST_F(NodeTest, decoratorMaxTime) {
    behavior._root = NodePtr(new MaxTime {NodePtr(new Trigger<Status::SUCCESS>{"name"}),5});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    std::this_thread::sleep_for( std::chrono::duration<double, std::milli>{1.0});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    std::this_thread::sleep_for( std::chrono::duration<double, std::milli>{6.0});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));


}

TEST_F(NodeTest, decoratorRepeater) {
    behavior._root = NodePtr(new Repeater {NodePtr(new Trigger<Status::SUCCESS>{"name"}),5});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(5, context->_blackBoard.getParam<int>("count", context->_behavior._id, behavior._root->_id));

}

TEST_F(NodeTest, decoratorRepeaterUntilSucces) {
    behavior._root = NodePtr(new RepeaterUntil{NodePtr(new LimiterAndToggle<Status::FAILURE,Status::SUCCESS>{3}),5,Status::SUCCESS});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(3, context->_blackBoard.getParam<int>("count", context->_behavior._id, behavior._root->_id));

}

TEST_F(NodeTest, decoratorRepeaterUntilLimit) {
    behavior._root = NodePtr(new RepeaterUntil{NodePtr(new LimiterAndToggle<Status::FAILURE,Status::SUCCESS>{7}),5,Status::SUCCESS});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(5, context->_blackBoard.getParam<int>("count", context->_behavior._id, behavior._root->_id));

}

TEST_F(NodeTest, decoratorRepeaterUntilFailure) {
    behavior._root = NodePtr(new RepeaterUntil{NodePtr(new LimiterAndToggle<Status::SUCCESS,Status::FAILURE>{4}),5,Status::FAILURE});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(4, context->_blackBoard.getParam<int>("count", context->_behavior._id, behavior._root->_id));

}


TEST_F(NodeTest, compositeSequence) {
    behavior._root = NodePtr(new Sequence{new Trigger<Status::SUCCESS> {"name"},new Trigger<Status::SUCCESS> {"name"},
                             new Trigger<Status::SUCCESS> {"name"},new Trigger<Status::FAILURE> {"name"}});
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));

}

TEST_F(NodeTest, compositeMemSequence) {
    behavior._root = NodePtr(new MemSequence{new Trigger<Status::SUCCESS> {"name"},new Trigger<Status::SUCCESS> {"name"},
                             new Toggle<Status::RUNNING,Status::SUCCESS>{"name"},new Trigger<Status::FAILURE> {"name"}});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(2, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
    EXPECT_EQ(Status::FAILURE, behavior._root->execute(*context));
    EXPECT_EQ(0, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(2, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
}



TEST_F(NodeTest, compositePriority) {
    behavior._root = NodePtr(new Priority{new Trigger<Status::SUCCESS> {"name"},new Trigger<Status::SUCCESS> {"name"},
                                          new Trigger<Status::SUCCESS> {"name"}});
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));

}


TEST_F(NodeTest, compositeMemPriority) {
    behavior._root = NodePtr(new MemPriority{new Trigger<Status::FAILURE> {"name"},new Trigger<Status::FAILURE> {"name"},
                                             new Toggle<Status::RUNNING,Status::FAILURE>{"name"},new Trigger<Status::SUCCESS> {"name"}});
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(2, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
    EXPECT_EQ(Status::SUCCESS, behavior._root->execute(*context));
    EXPECT_EQ(0, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
    EXPECT_EQ(Status::RUNNING, behavior._root->execute(*context));
    EXPECT_EQ(2, context->_blackBoard.getParam<std::size_t>("indexRunningChild", context->_behavior._id, behavior._root->_id));
}