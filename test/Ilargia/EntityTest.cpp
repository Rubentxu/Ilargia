#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include "Components/TestComponent.h"
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
    entity->addComponent(TestComponent{true});
    TestComponent r = entity->getComponent<TestComponent>();
    EXPECT_EQ(true, r._test);
    EXPECT_EQ(1, entity->getComponentIndices().size());
    EXPECT_EQ(std::type_index(typeid(TestComponent)), entity->getComponentIndices()[0]);
    EXPECT_EQ(true, entity->hasComponent<TestComponent>());
}
