#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include "gtest/gtest.h"
#include "core/Game.h"
#include "core/Engine.h"
#include "core/Manager.h"
#include "core/IOCContainer.h"
#include "Commons.h"

struct IOCContainerTest : public ::testing::Test {
    Ilargia::IOCContainer _container;

    virtual void SetUp() {

        //_container.registerInstance<Ilargia::Engine,TestEngine,Ilargia::Manager>();

    }

    virtual void TearDown() {
    }

};

TEST_F(IOCContainerTest, testConfig) {
    //_container.registerInstance<Ilargia::Manager,TestManager>();
    _container.getTypeID<Ilargia::Manager>();
    //auto manager = _container.getObject<Ilargia::Manager>();
    EXPECT_TRUE(true);

}