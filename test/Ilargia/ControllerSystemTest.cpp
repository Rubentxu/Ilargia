#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include <string>
#include <unordered_map>
#include "gtest/gtest.h"
#include "core/logicbrick/system/ControllerSystem.h"
#include "core/logicbrick/LogicBrick.h"

class TestControllerSystem : public Ilargia::ControllerSystem {
public:
    virtual bool validateSensors(std::unordered_map<std::string,std::unique_ptr<Ilargia::Sensor>>& sensors) override {
        Ilargia::ControllerSystem::validateSensors(sensors);
    }
};

class TestConditionalControllerSystem : public Ilargia::ConditionalControllerSystem {
public:
    void process(Ilargia::ConditionalController &controller) {
        Ilargia::ConditionalControllerSystem::process(controller);
    }

};

struct ControllerSystemTest: public ::testing::Test {
    std::shared_ptr<TestControllerSystem> controllerSystem;
    std::shared_ptr<TestConditionalControllerSystem> conditionalControllerSystem;
    Ilargia::Sensor *sensor;
    Ilargia::Sensor *sensor2;
    Ilargia::Controller controller;
    Ilargia::ConditionalController conditionalController;
    Ilargia::Actuator *actuator;

    virtual void SetUp() {
    }

    void initializeControllerSystem() {
        controllerSystem = std::make_shared<TestControllerSystem>();

        sensor = new Ilargia::Sensor{};
        sensor2 = new Ilargia::Sensor{};
        sensor->frequency = 1;
        controller = Ilargia::Controller {};
        controller.sensors.insert(std::make_pair<std::string,std::unique_ptr<Ilargia::Sensor>>(
                "SensorUno",std::unique_ptr<Ilargia::Sensor> (sensor)));
        controller.sensors.insert(std::make_pair<std::string,std::unique_ptr<Ilargia::Sensor>>(
                "SensorDos",std::unique_ptr<Ilargia::Sensor> (sensor2)));
    }

    void initializeConditionalControllerSystem() {
        conditionalControllerSystem = std::make_shared<TestConditionalControllerSystem>();

        sensor = new Ilargia::Sensor{};
        sensor2 = new Ilargia::Sensor{};
        sensor->frequency = 1;
        conditionalController = Ilargia::ConditionalController {};
        conditionalController.sensors.insert(std::make_pair<std::string,std::unique_ptr<Ilargia::Sensor>>(
                "SensorUno",std::unique_ptr<Ilargia::Sensor> (sensor)));
        conditionalController.sensors.insert(std::make_pair<std::string,std::unique_ptr<Ilargia::Sensor>>(
                "SensorDos",std::unique_ptr<Ilargia::Sensor> (sensor2)));

        actuator = new Ilargia::Actuator {};

        conditionalController.actuators.insert(std::make_pair<std::string,std::unique_ptr<Ilargia::Actuator>>(
                "ActuatorTest",std::unique_ptr<Ilargia::Actuator> (actuator)));


    }

    virtual void TearDown() {
    }

};



TEST_F(ControllerSystemTest, sizeSensor) {
    initializeControllerSystem();
    EXPECT_EQ(2, controller.sensors.size());
}

TEST_F(ControllerSystemTest, validateControllerProccess) {
    initializeControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    EXPECT_TRUE(controllerSystem->validateSensors(controller.sensors));

}

TEST_F(ControllerSystemTest, validateControllerNotProccess) {
    initializeControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_OFF;
    EXPECT_FALSE(controllerSystem->validateSensors(controller.sensors));

}



TEST_F(ControllerSystemTest, conditionalControllerAND) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_AND;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerNAND) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_NAND;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);


}

TEST_F(ControllerSystemTest, conditionalControllerOR) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_OR;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerNOR) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_NOR;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerXOR) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_XOR;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerXNOR) {
    initializeConditionalControllerSystem();
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_XNOR;

    sensor->positive = false;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

    sensor->positive = false;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF,conditionalController.pulseState);

    sensor->positive = true;
    sensor2->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON,conditionalController.pulseState);

}





