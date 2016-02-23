#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "NodeTest.h"


using namespace bt;

//using ::testing::Return;
template <Status T>
using TriggerPtr = std::shared_ptr<Trigger<T>>;

NodeTest::~NodeTest() { };

void NodeTest::SetUp() {
    auto nodep =  std::make_shared<Action>("name");
    behavior = std::make_shared<BehaviorTree>(std::make_shared<Action>("name")) ;

};

void NodeTest::TearDown() { };



TEST_F(NodeTest, triggerAction) {
    node = TriggerPtr<Status::SUCCESS>{};
    EXPECT_EQ(Status::SUCCESS,node->tick(behavior->_context));
}



