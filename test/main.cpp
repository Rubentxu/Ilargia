#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
