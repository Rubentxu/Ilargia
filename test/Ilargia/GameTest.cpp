#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"


class GameTest: public ::testing::Test {
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

};

TEST_F(GameTest, triggerActionFailure) {

    EXPECT_EQ(true, true);
}
