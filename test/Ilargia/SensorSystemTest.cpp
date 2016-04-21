#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#include "gtest/gtest.h"
#include "Commons.h"
#include "core/logicbrick/LogicBrick.h"


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

TEST_F(SensorSystemTest, delaySensorTest) {
    Ilargia::DelaySensorSystem delaySensorSystem {};
    Ilargia::DelaySensor delaySensor {1,1};

    EXPECT_FALSE(delaySensorSystem.query(delaySensor,0.5));
    EXPECT_TRUE(delaySensorSystem.query(delaySensor,0.5));
    EXPECT_TRUE(delaySensorSystem.query(delaySensor,0.5));
    EXPECT_FALSE(delaySensorSystem.query(delaySensor,0.5));
    EXPECT_FALSE(delaySensorSystem.query(delaySensor,0.5));

}

TEST_F(SensorSystemTest, keyboardSensorTest) {
    Ilargia::KeyboardSensorSystem sensorSystem {};
    Ilargia::KeyboardSensor sensor {100,false, false};

    sensorSystem.keysCodeSignal[100] = true;
    EXPECT_TRUE(sensorSystem.query(sensor,0.5));

    sensorSystem.keysCodeSignal[100] = false;
    EXPECT_FALSE(sensorSystem.query(sensor,0.5));

}

struct BodyTest {};
struct ContactTest {};

TEST_F(SensorSystemTest, nearSensorTest) {
    Ilargia::NearSensorSystem<BodyTest,ContactTest> sensorSystem {};
    Ilargia::NearSensor<BodyTest,ContactTest> sensor {};
    ContactTest contact{};

    EXPECT_FALSE(sensorSystem.query(sensor,0.5));

    sensor.distanceContactList.push_back(contact);
    EXPECT_TRUE(sensorSystem.query(sensor,0.5));

    sensor.distanceContactList.pop_back();
    sensor.resetDistanceContactList.push_back(contact);
    EXPECT_TRUE(sensorSystem.query(sensor,0.5));


}
