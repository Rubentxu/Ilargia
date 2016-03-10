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

    EntityTest(): entity{new Entity} {}

    virtual void SetUp() override {

    }

    virtual void TearDown( ){
        //delete entity;
    }

};

TEST_F(EntityTest, addComponent) {
    entity->addComponent(TestComponent{true});
    EXPECT_EQ(true, entity->hasComponent<TestComponent>());
}

TEST_F(EntityTest, getComponent) {
    entity->addComponent(TestComponent{true});
    TestComponent r = entity->getComponent<TestComponent>();
    EXPECT_EQ(true, r._test);

}

TEST_F(EntityTest, removeComponent) {
    entity->addComponent(TestComponent{true});
    TestComponent r = entity->getComponent<TestComponent>();
    EXPECT_EQ(true, r._test);
    entity->removeComponent<TestComponent>();
    //EXPECT_EQ(false, entity->hasComponent<TestComponent>());

}
