#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include <Entity.h>

using namespace Entitas;

class EntityTest: public ::testing::Test {
public:
    Entity* entity;

    EntityTest() : entity{new Entity{}}  {};

    virtual void SetUp() override {

    }
    virtual void TearDown(){}
};

TEST_F(EntityTest, addComponent) {
    entity->addComponent(3,TestComponent{true});
    EXPECT_EQ(true, entity->getComponent<TestComponent>(3)._test);
    EXPECT_EQ(false, entity->getComponent<TestComponent>(1)._test);
    EXPECT_EQ(1, entity->getComponentIndices().size());
    EXPECT_EQ(3, entity->getComponentIndices()[0]);
}
