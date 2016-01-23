#include <iostream>
#include "any.h"
#include "anyTest.h"


using ::testing::Return;


anyTest::anyTest() {
    // Have qux return true by default
    ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    ON_CALL(m_bar,norf()).WillByDefault(Return(false));
}

anyTest::~anyTest() {};

void anyTest::SetUp() {};

void anyTest::TearDown() {};

class testObject {
public:
    int _value;

    testObject(int val): _value{val}{}

};

std::ostream& operator<<(std::ostream& out, const testObject& b)
{
        out << b._value;

    return out ;
}

TEST_F(anyTest, typeBool) {
    any a0 = true;
    EXPECT_EQ( a0._<bool>() , true);

}

TEST_F(anyTest, typeChar) {
    any a1 = 'A';
    EXPECT_EQ( a1._<char>() , 'A');

}

TEST_F(anyTest, typeInt) {
    any a2 = 6;
    EXPECT_EQ( a2._<int>(), 6);

}

TEST_F(anyTest, typeDouble) {
    any a3 = 3.14;
    EXPECT_EQ( a3._<double>() , 3.14);

}

TEST_F(anyTest, typeChars) {
    any a4 = "hello,";
    auto expected = "hello,";
    EXPECT_EQ( a4._<const char*>() , expected);
}

TEST_F(anyTest, typeVectorInt) {
    any a5 = std::vector<int>{6, 5, 4, 3, 2, 1, 0};
    auto expected = std::vector<int>{ 6, 5, 4, 3, 2, 1, 0 };
    EXPECT_EQ( a5._<std::vector<int>>() , expected);
}

TEST_F(anyTest, typeString) {
    any a6 = std::string("world!");
    EXPECT_EQ( a6._<std::string>() , "world!");
}

TEST_F(anyTest, typeStruct) {
    any a7 = testObject{3};
    std::cout << "[7] testObject      : " << a7._<testObject>() << std::endl;
    EXPECT_TRUE(a7.is<testObject>());
}
