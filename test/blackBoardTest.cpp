#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "BlackBoard.h"
#include "blackBoardTest.h"

using namespace bt;
//using ::testing::Return;

blackBoardTest::blackBoardTest() {
//    // Have qux return true by default
//    ON_CALL(m_bar, qux()).WillByDefault(Return(true));
//    // Have norf return false by default
//    ON_CALL(m_bar, norf()).WillByDefault(Return(false));
}


BlackBoard b0;

blackBoardTest::~blackBoardTest() { };

void blackBoardTest::SetUp() { };

void blackBoardTest::TearDown() { };


class testObject {
    int _value;
    std::string _name;
public:

    testObject() : _value{0} , _name{"test"}{ }
    testObject(int val, std::string name) : _value{val} , _name{name}{ }

    bool operator==(const testObject &other) const {
        return _value == other._value && _name == other._name;;
    }


};

TEST_F(blackBoardTest, typeBool) {
    EXPECT_EQ(true,b0.setParam("isCheck",true));
    EXPECT_EQ(true, b0.getParam<bool>("isCheck"));
}

TEST_F(blackBoardTest, typeChar) {
    EXPECT_EQ(true,b0.setParam("myChar",'A'));
    EXPECT_EQ('A', b0.getParam<char>("myChar"));

}

TEST_F(blackBoardTest, typeInt) {
    EXPECT_EQ(true,b0.setParam("myInt",6));
    EXPECT_EQ(6, b0.getParam<int>("myInt"));

}

TEST_F(blackBoardTest, typeDouble) {
    EXPECT_EQ(true,b0.setParam("myDouble",3.14));
    EXPECT_EQ(3.14, b0.getParam<double>("myDouble"));

}

TEST_F(blackBoardTest, typeChars) {
    EXPECT_EQ(true,b0.setParam("myChars","hello,"));
    EXPECT_EQ("hello,", b0.getParam<const char *>("myChars"));
}


TEST_F(blackBoardTest, typeVectorInt) {
    auto expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(true,b0.setParam("myVector",std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
    EXPECT_EQ(expected, b0.getParam<std::vector<int>>("myVector"));

}

TEST_F(blackBoardTest, typeString) {
    EXPECT_EQ(true,b0.setParam("myString",std::string("world!")));
    auto result = b0.getParam<std::string>("myString");
    EXPECT_EQ("world!", result);
}

TEST_F(blackBoardTest, typeStruct) {
    EXPECT_EQ(true,b0.setParam("myStruct", testObject{3,"Pruebas"}));
    auto actual = testObject{3,"Pruebas"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct"), actual);
}

TEST_F(blackBoardTest, typeStructTreeScope) {
    EXPECT_EQ(true,b0.setParam("myStruct", testObject{3,"Pruebas2"},"TreeTest"));
    auto actual = testObject{3,"Pruebas2"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct","TreeTest"), actual);
}


TEST_F(blackBoardTest, typeStructNodeScope) {
    EXPECT_EQ(true,b0.setParam("myStruct", testObject{3,"Pruebas3"},"TreeTest","NodeTest"));
    auto actual = testObject{3,"Pruebas3"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct","TreeTest","NodeTest"), actual);
}

