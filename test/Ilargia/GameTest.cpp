#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include <thread>
#include "gtest/gtest.h"
#include "core/Game.h"


class TestManager : public Ilargia::Manager {
};

class TestEngine : public Ilargia::Engine {
public:
    bool isConfigure = false;
    bool isInitSystem = false;
    bool isProcessInput = false;
    bool isUpdate = false;
    bool isRender = false;
    bool isShutdown = false;

    TestEngine(std::shared_ptr<Ilargia::Manager> &&manager) : Engine(std::move(manager)) { }

    virtual void configure(std::vector<std::string> &args) override {
        isConfigure = (args[0] == "true") ? true : false;
    }

    virtual void initSystems() override {
        isInitSystem = true;
    }


    virtual void processInput() override {
        isProcessInput = true;

        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            shutdownEngine(1);
        }).detach();
    }

    virtual void update(float deltaTime) override {
        isUpdate = !isUpdate;
    }

    virtual void render() override {
        isRender = true;
    }

    virtual void shutdown() override {
        isShutdown = true;
    }

};

class TestTimer : public Ilargia::Timer {
public:
    TestTimer() : Timer() { }

    virtual double getSecondsTime() override {
        return 0.016666666666666666;
    }

};

struct GameTest : public ::testing::Test {
    std::shared_ptr<Ilargia::Engine> _engine;
    std::shared_ptr<Ilargia::Timer> _timer;
    std::shared_ptr<Ilargia::Game> _game;

    virtual void SetUp() {
        _timer = std::make_shared<TestTimer>();
        _engine = std::make_shared<TestEngine>(std::make_shared<TestManager>());
        _game = std::make_shared<Ilargia::Game>(_engine, _timer);
    }

    virtual void TearDown() {
    }

};

TEST_F(GameTest, testInitEngine) {
    char *argv[]{"test.exe", "true", "test"};
    _game->init(3, argv);
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isConfigure);
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isInitSystem);

}

TEST_F(GameTest, testRunEngine) {
    _game->runGame();
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isProcessInput);
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isUpdate);
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isRender);

}
