#include "gtest/gtest.h"

// The fixture for testing class Foo.
class blackBoardTest : public ::testing::Test {

protected:
    blackBoardTest();

    virtual ~blackBoardTest();

    virtual void SetUp();

    virtual void TearDown();

};
