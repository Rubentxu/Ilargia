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
    b0.set("name",std::string{"Juan"});

    EXPECT_EQ(true, b0.get<bool>("isCheck"));
    EXPECT_EQ("Juan", b0.get<std::string>("name"));

}

TEST_F(blackBoardTest, typeChar) {
    blackBoard b0 {};
    b0.set("myChar",'A');
    EXPECT_EQ('A', b0.get<char>("myChar"));

}

TEST_F(blackBoardTest, typeInt) {
    blackBoard b0 {};
    b0.set("myInt",6);
    EXPECT_EQ(6, b0.get<int>("myInt"));

}

TEST_F(blackBoardTest, typeDouble) {
    blackBoard b0 {};
    b0.set("myDouble",3.14);
    EXPECT_EQ(3.14, b0.get<double>("myDouble"));

}

TEST_F(blackBoardTest, typeChars) {
    blackBoard b0 {};
    b0.set("myChars","hello,");
    EXPECT_EQ("hello,", b0.get<const char *>("myChars"));
}

TEST_F(blackBoardTest, typeVectorInt) {
    blackBoard b0 {};
    auto expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
    b0.setVector("myVector",std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});

    EXPECT_EQ(expected, b0.get<std::vector<int>>("myVector"));

}

TEST_F(blackBoardTest, typeString) {
    blackBoard b0 {};
    b0.set("myString",std::string("world!"));
    auto result = b0.get<std::string>("myString");
    EXPECT_EQ("world!", result);
}

//TEST_F(blackBoardTest, typeStruct) {
//    blackBoard b0 {};
//    b0.set("myStruct", testObject{3});
//    EXPECT_EQ(b0.get<testObject>("myStruct"), "world!");
//}

