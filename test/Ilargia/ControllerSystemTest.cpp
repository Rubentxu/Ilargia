#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include <unordered_map>
#include "gtest/gtest.h"
#include "core/logicbrick/system/ControllerSystem.h"

class TestControllerSystem : public Ilargia::ControllerSystem {
public:
    virtual bool validateSensors(std::unordered_map<std::string, std::unique_ptr<Ilargia::Sensor>> &sensors) override {
        Ilargia::ControllerSystem::validateSensors(sensors);
    }
};

class TestConditionalControllerSystem : public Ilargia::ConditionalControllerSystem {
public:
    void process(Ilargia::ConditionalController &controller) {
        Ilargia::ConditionalControllerSystem::process(controller);
    }

};


class TestScriptControllerSystem : public Ilargia::ScriptControllerSystem {
public:
    void process(Ilargia::ScriptController &controller) {
        Ilargia::ScriptControllerSystem::process(controller);
    }

};

struct ControllerSystemTest : public ::testing::Test {
    std::shared_ptr<TestControllerSystem> controllerSystem;
    std::shared_ptr<TestConditionalControllerSystem> conditionalControllerSystem;
    std::shared_ptr<TestScriptControllerSystem> scriptControllerSystem;
    Ilargia::Sensor *sensor;
    Ilargia::Sensor *sensor2;
    Ilargia::Sensor *sensor3;
    Ilargia::Sensor *sensor4;
    Ilargia::Controller controller;
    Ilargia::ConditionalController conditionalController;
    Ilargia::Actuator *actuator;

    virtual void SetUp() {
        sensor = new Ilargia::Sensor{};
        sensor2 = new Ilargia::Sensor{};
        sensor3 = new Ilargia::Sensor{};
        sensor4 = new Ilargia::Sensor{};
        sensor3->pulseState = Ilargia::BrickMode::BM_ON;
        sensor4->pulseState = Ilargia::BrickMode::BM_ON;
        sensor->frequency = 1;
        actuator = new Ilargia::Actuator{};
        controllerSystem = std::make_shared<TestControllerSystem>();

        controller.sensors.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Sensor>>(
                "SensorUno", std::unique_ptr<Ilargia::Sensor>(sensor)));
        controller.sensors.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Sensor>>(
                "SensorDos", std::unique_ptr<Ilargia::Sensor>(sensor2)));

        conditionalControllerSystem = std::make_shared<TestConditionalControllerSystem>();

        conditionalController.sensors.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Sensor>>(
                "SensorUno", std::unique_ptr<Ilargia::Sensor>(sensor3)));
        conditionalController.sensors.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Sensor>>(
                "SensorDos", std::unique_ptr<Ilargia::Sensor>(sensor4)));
        conditionalController.actuators.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Actuator>>(
                "ActuatorTest", std::unique_ptr<Ilargia::Actuator>(actuator)));

    }


    virtual void TearDown() {

    }

};


TEST_F(ControllerSystemTest, sizeSensor) {
    EXPECT_EQ(2, controller.sensors.size());

}

TEST_F(ControllerSystemTest, validateControllerProccess) {
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_ON;

    EXPECT_TRUE(controllerSystem->validateSensors(controller.sensors));

}

TEST_F(ControllerSystemTest, validateControllerNotProccess) {
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    sensor2->pulseState = Ilargia::BrickMode::BM_OFF;
    EXPECT_FALSE(controllerSystem->validateSensors(controller.sensors));

}

TEST_F(ControllerSystemTest, conditionalControllerAND) {
    conditionalController.op = Ilargia::Op::OP_AND;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerNAND) {

    sensor3->pulseState = Ilargia::BrickMode::BM_ON;
    sensor4->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_NAND;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);


}

TEST_F(ControllerSystemTest, conditionalControllerOR) {

    sensor3->pulseState = Ilargia::BrickMode::BM_ON;
    sensor4->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_OR;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerNOR) {

    sensor3->pulseState = Ilargia::BrickMode::BM_ON;
    sensor4->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_NOR;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerXOR) {

    sensor3->pulseState = Ilargia::BrickMode::BM_ON;
    sensor4->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_XOR;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, conditionalControllerXNOR) {

    sensor3->pulseState = Ilargia::BrickMode::BM_ON;
    sensor4->pulseState = Ilargia::BrickMode::BM_ON;
    conditionalController.op = Ilargia::Op::OP_XNOR;

    sensor3->positive = false;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

    sensor3->positive = false;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = false;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_OFF, conditionalController.pulseState);

    sensor3->positive = true;
    sensor4->positive = true;
    conditionalControllerSystem->process(conditionalController);
    EXPECT_EQ(Ilargia::BrickMode::BM_ON, conditionalController.pulseState);

}

TEST_F(ControllerSystemTest, scriptProccess) {
    scriptControllerSystem = std::make_shared<TestScriptControllerSystem>();
    Ilargia::ScriptController scontroller {};
    Ilargia::Sensor *sensor = new Ilargia::Sensor{};
    sensor->pulseState = Ilargia::BrickMode::BM_ON;
    Ilargia::Actuator *actuator = new Ilargia::Actuator{};

    scontroller.sensors.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Sensor>>(
            "Sensor", std::unique_ptr<Ilargia::Sensor>(sensor)));
    scontroller.actuators.insert(std::make_pair<std::string, std::unique_ptr<Ilargia::Actuator>>(
            "Actuator", std::unique_ptr<Ilargia::Actuator>(actuator)));
    scontroller.script = [] (Ilargia::Controller& controller) {
        for (auto &pair : controller.actuators) {
            pair.second->isActive = true;
        }
    };
    scriptControllerSystem->process(scontroller);
    EXPECT_TRUE(actuator->isActive);

}




