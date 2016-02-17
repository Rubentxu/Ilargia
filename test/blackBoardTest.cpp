#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "BlackBoard.h"
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
    BlackBoard b0{};
    b0.setParam("isCheck",true);
    auto value = b0.getParam<bool>("isCheck");
    EXPECT_EQ(true, value);
}
/*
    b0.setParam("isCheck",true);
    b0.setParam("name",std::string{"Juan"});

    EXPECT_EQ(true, b0.getParam<bool>("isCheck"));
    EXPECT_EQ("Juan", b0.getParam<std::string>("name"));

}

TEST_F(blackBoardTest, typeChar) {
    BlackBoard b0 {};
    b0.setParam("myChar",'A');
    EXPECT_EQ('A', b0.getParam<char>("myChar"));

}

TEST_F(blackBoardTest, typeInt) {
    BlackBoard b0 {};
    b0.setParam("myInt",6);
    EXPECT_EQ(6, b0.getParam<int>("myInt"));

}

TEST_F(blackBoardTest, typeDouble) {
    BlackBoard b0 {};
    b0.setParam("myDouble",3.14);
    EXPECT_EQ(3.14, b0.getParam<double>("myDouble"));

}

TEST_F(blackBoardTest, typeChars) {
    BlackBoard b0 {};
    b0.setParam("myChars","hello,");
    EXPECT_EQ("hello,", b0.getParam<const char *>("myChars"));
}

*/
/*TEST_F(blackBoardTest, typeVectorInt) {
    BlackBoard b0 {};
    auto expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
    b0.setParamVector("myVector",std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});

    EXPECT_EQ(expected, b0.get<std::vector<int>>("myVector"));

}*//*


TEST_F(blackBoardTest, typeString) {
    BlackBoard b0 {};
    b0.setParam("myString",std::string("world!"));
    auto result = b0.getParam<std::string>("myString");
    EXPECT_EQ("world!", result);
}

TEST_F(blackBoardTest, typeStruct) {
    BlackBoard b0 {};
    b0.setParam("myStruct", testObject{3,"Pruebas"});
    auto actual = testObject{3,"Pruebas"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct"), actual);
}
*/

