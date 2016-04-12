#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include "gtest/gtest.h"
#include "core/Engine.h"
#include <string>


struct TypeVectorTest: public ::testing::Test {

    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

};


class ExtendUno : public std::string {
public:
    ExtendUno(std::string cadena) : std::string(cadena){}
};
class ExtendDos : public std::string {
public:
    ExtendDos(std::string cadena) : std::string(cadena){}
};
class ExtendTres : public std::string {
public:
    ExtendTres(std::string cadena) : std::string(cadena){}
};
class ExtendCuatro : public std::string {
public:
    ExtendCuatro(std::string cadena) : std::string(cadena){}
};




TEST_F(TypeVectorTest, testGetType) {
    Ilargia::TypeVector<std::string> array{ExtendUno{"Uno"},ExtendDos{"Dos"},ExtendTres{"Tres"},ExtendCuatro{"Cuatro"}};
    auto id = array.getTypeID<ExtendUno>();
    auto id2 = array.getTypeID<ExtendDos>();
    auto id3 = array.getTypeID<ExtendTres>();
    auto id4 = array.getTypeID<ExtendCuatro>();

    EXPECT_EQ(0,id);
    EXPECT_EQ(1,id2);
    EXPECT_EQ(2,id3);
    EXPECT_EQ(3,id4);

}

TEST_F(TypeVectorTest, testAddItem) {
    Ilargia::TypeVector<std::string> array{ExtendUno{"Uno"},ExtendDos{"Dos"},ExtendTres{"Tres"},ExtendCuatro{"Cuatro"}};


    EXPECT_EQ("Uno",array.get<ExtendUno>());
    EXPECT_EQ("Dos",array.get<ExtendDos>());
    EXPECT_EQ("Tres",array.get<ExtendTres>());
    EXPECT_EQ("Cuatro",array.get<ExtendCuatro>());

}