#include <iostream>
#include "blackBoard.h"
#include "blackBoardTest.h"

//using ::testing::Return;

blackBoardTest::blackBoardTest() {
//    // Have qux return true by default
//    ON_CALL(m_bar, qux()).WillByDefault(Return(true));
//    // Have norf return false by default
//    ON_CALL(m_bar, norf()).WillByDefault(Return(false));
}

blackBoardTest::~blackBoardTest() { };

void blackBoardTest::SetUp() { };

void blackBoardTest::TearDown() { };


class testObject {
public:
    int _value;

    testObject(int val) : _value{val} { }

};

TEST_F(blackBoardTest, typeBool) {
    blackBoard b0 {};
    b0.set("isCheck",true);
    auto result = b0.get<bool>("isCheck");
    EXPECT_EQ(result, true);

}

//TEST_F(blackBoardTest, typeChar) {
//    blackBoard b0 {};
//    b0.set("myChar",'A');
//    EXPECT_EQ(b0.get<char>("myChar"), 'A');
//
//}

TEST_F(blackBoardTest, typeInt) {
    blackBoard b0 {};
    b0.set("myInt",6);
    EXPECT_EQ(b0.get<int>("myInt"), 6);
    EXPECT_TRUE(b0.is<int>("myInt"));

}

TEST_F(blackBoardTest, typeDouble) {
    blackBoard b0 {};
    b0.set("myDouble",3.14);
    EXPECT_EQ(b0.get<double>("myDouble"), 3.14);

}

TEST_F(blackBoardTest, typeChars) {
    blackBoard b0 {};
    b0.set("myChars","hello,");
    EXPECT_EQ(b0.get<const char *>("myChars"), "hello,");
}

TEST_F(blackBoardTest, typeVectorInt) {
    blackBoard b0 {};
    b0.set("myVector",std::vector<int>{6, 5, 4, 3, 2, 1, 0});
    auto expected = std::vector<int>{6, 5, 4, 3, 2, 1, 0};
    EXPECT_EQ(b0.get<std::vector<int>>("myVector"), expected);

}

TEST_F(blackBoardTest, typeString) {
    blackBoard b0 {};
    b0.set("myString",std::string("world!"));
    auto result = b0.get<int>("myString");
    EXPECT_EQ(result, 1);
}

//TEST_F(blackBoardTest, typeStruct) {
//    blackBoard b0 {};
//    b0.set("myStruct", testObject{3});
//    EXPECT_EQ(b0.get<testObject>("myStruct"), "world!");
//}

