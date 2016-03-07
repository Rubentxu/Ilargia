#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include <Entity.h>

using namespace Entitas;

class TestComponent: public IComponent {
public:
    bool test = false;
};

using namespace Entitas;

class EntityTest: public ::testing::Test {
public:
    Entity* entity;

    EntityTest() : entity{new Entity{100}}  {};

    virtual void SetUp() override {

    }

    virtual void TearDown(){}
};

TEST_F(EntityTest, addComponent) {
    entity->addComponent(1,TestComponent{});
    EXPECT_EQ(true, true);
}
