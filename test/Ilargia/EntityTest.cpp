#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"


class EntityTest: public ::testing::Test {

};

TEST_F(EntityTest, triggerActionFailure) {

    EXPECT_EQ(true, true);
}
