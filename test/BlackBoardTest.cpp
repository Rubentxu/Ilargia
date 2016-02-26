#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include <iostream>
#include "BlackBoard.h"
#include "BlackBoardTest.h"
#include <boost/any.hpp>

using namespace bt;
//using ::testing::Return;

BlackBoardTest::BlackBoardTest() {
//    // Have qux return true by default
//    ON_CALL(m_bar, qux()).WillByDefault(Return(true));
//    // Have norf return false by default
//    ON_CALL(m_bar, norf()).WillByDefault(Return(false));
}


BlackBoard b0;

BlackBoardTest::~BlackBoardTest() { };

void BlackBoardTest::SetUp() { };

void BlackBoardTest::TearDown() { };


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


bool key_compare (Memory const &lhs, Memory const &rhs) {
    auto pred = [] (decltype(*lhs.begin()) a, decltype(*lhs.begin()) b)
    { return a.first == b.first; };

    return lhs.size() == rhs.size()
           && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
}

TEST_F(BlackBoardTest, typeBool) {
    b0.setParam("isCheck",true);
    EXPECT_EQ(true, b0.getParam<bool>("isCheck"));
    b0.setParam("isCheck",false);
    EXPECT_EQ(false, b0.getParam<bool>("isCheck"));
}

TEST_F(BlackBoardTest, typeChar) {
    b0.setParam("myChar",'A');
    EXPECT_EQ('A', b0.getParam<char>("myChar"));

}

TEST_F(BlackBoardTest, typeInt) {
    b0.setParam("myInt",6);
    EXPECT_EQ(6, b0.getParam<int>("myInt"));

}

TEST_F(BlackBoardTest, typeDouble) {
    b0.setParam("myDouble",3.14);
    EXPECT_EQ(3.14, b0.getParam<double>("myDouble"));

}

TEST_F(BlackBoardTest, typeChars) {
    b0.setParam("myChars","hello,");
    EXPECT_EQ("hello,", b0.getParam<const char *>("myChars"));
}


TEST_F(BlackBoardTest, typeVectorInt) {
    auto expected = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
    b0.setParam("myVector",std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    EXPECT_EQ(expected, b0.getParam<std::vector<int>>("myVector"));

}

TEST_F(BlackBoardTest, typeString) {
    b0.setParam("myString",std::string("world!"));
    auto result = b0.getParam<std::string>("myString");
    EXPECT_EQ("world!", result);
}

TEST_F(BlackBoardTest, typeStruct) {
    b0.setParam("myStruct", testObject{3,"Pruebas"});
    auto actual = testObject{3,"Pruebas"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct"), actual);
}

TEST_F(BlackBoardTest, typeStructTreeScope) {
    b0.setParam("myStruct", testObject{3,"Pruebas2"},"TreeTest");
    auto actual = testObject{3,"Pruebas2"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct","TreeTest"), actual);
}


TEST_F(BlackBoardTest, typeStructNodeScope) {
    b0.setParam("myStruct", testObject{3,"Pruebas3"},"TreeTest","NodeTest");
    auto actual = testObject{3,"Pruebas3"};
    EXPECT_EQ(b0.getParam<testObject>("myStruct","TreeTest","NodeTest"), actual);
}


TEST_F(BlackBoardTest, baseMemories) {
    Memory& baseMemory = b0.getMemory();
    baseMemory.insert(std::make_pair("isCheck2",true));
    auto it = baseMemory.find("isCheck2");

    EXPECT_NE( baseMemory.end(), it );
    EXPECT_EQ("isCheck2", it->first);
    EXPECT_EQ(true, boost::any_cast<bool>(it->second));

    Memory& memory = b0.getMemory("tree");
    auto it2 = memory.find("isCheck2");

    EXPECT_EQ(memory.end(), it2);

}


TEST_F(BlackBoardTest, treeMemories) {
    Memory& treeMemory = b0.getMemory("tree");
    treeMemory.insert(std::make_pair("Value",3));
    auto ita = treeMemory.find("Value");

    EXPECT_NE( treeMemory.end(), ita );
    EXPECT_EQ("Value", ita->first);
    EXPECT_EQ(3, boost::any_cast<int>(ita->second));

    Memory& memory = b0.getMemory();
    auto itb = memory.find("Value");

    EXPECT_EQ(memory.end(), itb);

    Memory& treeMemory2 = b0.getMemory("tree");
    EXPECT_TRUE(key_compare(treeMemory, treeMemory2));

}


TEST_F(BlackBoardTest, nodeMemories) {
    Memory& nodeMemory = b0.getMemory("tree","scope");
    nodeMemory.insert(std::make_pair("ValueScope",50));
    auto ita = nodeMemory.find("ValueScope");

    EXPECT_NE( nodeMemory.end(), ita );
    EXPECT_EQ("ValueScope", ita->first);
    EXPECT_EQ(50, boost::any_cast<int>(ita->second));

    Memory& memory = b0.getMemory("tree");
    auto itb = memory.find("ValueScope");

    EXPECT_EQ(memory.end(), itb);

    Memory& nodeMemory2 = b0.getMemory("tree","scope");
    EXPECT_TRUE(key_compare(nodeMemory, nodeMemory2));
}