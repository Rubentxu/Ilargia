#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include "gtest/gtest.h"
#include "core/Game.h"
#include "core/IOCContainer.h"
#include "Commons.h"

struct IOCContainerTest : public ::testing::Test {
    Ilargia::IOCContainer _container;

    virtual void SetUp() { }

    virtual void TearDown() { }

};

class IObject {
public:
    virtual ~IObject() { }

    virtual bool test() = 0;
};

class IOtherObject {
public:
    virtual ~IOtherObject() { }

    virtual bool otherTest() = 0;
};

class Object : public IObject {
public:
    Object() { }

    bool test() {
        return true;
    }
};

class OtherObject : public IOtherObject {
    std::shared_ptr<IObject> _object;
public:
    OtherObject(std::shared_ptr<IObject> object) : _object(object) {}

    bool otherTest() override {
        return _object->test();
    }
};


TEST_F(IOCContainerTest, testTypeId) {
    EXPECT_EQ(0, _container.getTypeID<IObject>());
}

TEST_F(IOCContainerTest, testGetObject) {
    _container.registerInstance<IObject, Object>();
    EXPECT_EQ(1, _container.m_factories.size());
    auto object = _container.getObject<IObject>();
    EXPECT_TRUE(object->test());
}

TEST_F(IOCContainerTest, testGetOtherObject) {
    _container.registerInstance<IObject, Object>();
    _container.registerFactory<IOtherObject,OtherObject,IObject>();
    EXPECT_EQ(2, _container.m_factories.size());
    auto otherObject = _container.getObject<IOtherObject>();
    EXPECT_TRUE(otherObject->otherTest());
}