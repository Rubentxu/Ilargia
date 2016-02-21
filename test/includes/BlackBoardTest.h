#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"

// The fixture for testing class Foo.
class BlackBoardTest : public ::testing::Test {

protected:
    BlackBoardTest();

    virtual ~BlackBoardTest();

    virtual void SetUp();

    virtual void TearDown();

};
