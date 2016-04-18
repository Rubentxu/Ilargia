#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include "Commons.h"
#include "core/logicbrick/sensor/Sensor.h"


class SensorSystemTest: public ::testing::Test {
public:
    std::shared_ptr<TestSensorSystem> system;
    Ilargia::Sensor sensor;

    virtual void SetUp() {
        system = std::make_shared<TestSensorSystem>();
        sensor.frequency = 1;
    }

    virtual void TearDown() {
    }

};

TEST_F(SensorSystemTest, defaultTest) {
    system->queryIsTrue = false;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseModeTrueTest) {
    system->queryIsTrue = false;
    sensor.pulse = Ilargia::Pulse::PM_TRUE;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}



TEST_F(SensorSystemTest, pulseModeFalseTest) {
    system->queryIsTrue = false;
    sensor.pulse = Ilargia::Pulse::PM_FALSE;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseModeBothTest) {
    system->queryIsTrue = false;
    sensor.pulse = Ilargia::Pulse::PM_BOTH;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}


TEST_F(SensorSystemTest, inverseTest) {
    system->queryIsTrue = false;
    sensor.invert = true;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_TRUE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseModeTrueInverTest) {
    system->queryIsTrue = false;
    sensor.invert = true;
    sensor.pulse = Ilargia::Pulse::PM_TRUE;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_TRUE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseModeFalseInverTest) {
    system->queryIsTrue = false;
    sensor.invert = true;
    sensor.pulse = Ilargia::Pulse::PM_FALSE;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_TRUE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);
}

TEST_F(SensorSystemTest, pulseModeBothInverTest) {
    system->queryIsTrue = false;
    sensor.invert = true;
    sensor.pulse = Ilargia::Pulse::PM_BOTH;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_TRUE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);
}


TEST_F(SensorSystemTest, tapTest) {
    system->queryIsTrue = false;
    sensor.tap = true;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseModeTrueTapTest) {
    system->queryIsTrue = false;
    sensor.tap = true;
    sensor.pulse = Ilargia::Pulse::PM_TRUE;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}


TEST_F(SensorSystemTest, pulseChangeStateTest) {
    system->queryIsTrue = false;
    sensor.frequency = 0;
    sensor.pulse = Ilargia::Pulse::PM_BOTH;

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->queryIsTrue = true;
    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,true,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_TRUE(sensor.positive);

    system->queryIsTrue = false;
    system->processSensor(sensor,false,0.5);
    EXPECT_FALSE(sensor.positive);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);


    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);

    system->processSensor(sensor,false,0.5);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, sensor.pulseState);
    EXPECT_FALSE(sensor.positive);
}