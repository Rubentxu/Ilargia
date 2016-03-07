#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include <Entity.h>

using namespace Entitas;

class EntityTest: public ::testing::Test {
public:
    std::unique_ptr<Entity> entity;

    EntityTest() {};

    virtual void SetUp() override {
        entity = std::unique_ptr<Entity>();
    }

    virtual void TearDown(){}
};

TEST_F(EntityTest, addComponent) {

    EXPECT_EQ(true, true);
}
