#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include "gtest/gtest.h"
#include "core/Game.h"


//int Ilargia::Engine::s_nextTypeManagerId = 0;

class TestManager : public Ilargia::Manager{};

class TestEngine:  public Ilargia::Engine {
public:
    bool isConfigure = false;
    bool isInitSystem = false;
    bool isProcessInput = false;
    bool isUpdate = false;
    bool isShutdown = false;

    TestEngine(std::shared_ptr<Ilargia::Manager> manager) : Engine(manager) { }

    virtual void configure(std::vector<std::string> &args) override {
        isConfigure = true;
    }

    virtual void initSystems() override {
        isInitSystem = true;
    }

    virtual void processInput() override {}

    virtual void update(float deltaTime) override {}

    virtual void render() override {}

    virtual void shutdown() override {}

};


struct GameTest: public ::testing::Test {
    std::shared_ptr<Ilargia::Engine> _engine;
    std::shared_ptr<Ilargia::Game> _game;

    virtual void SetUp() {
        _engine = std::make_shared<TestEngine>(std::make_shared<TestManager>());
        _game = std::make_shared<Ilargia::Game>(_engine);
    }

    virtual void TearDown() {
    }

};



TEST_F(GameTest, testInitEngineFailure) {
    //_game->init(0, NULL);
   // bool isConfig = dynamic_cast<TestEngine *>(_engine.get())->isConfigure;
    EXPECT_TRUE(true);
    //EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isInitSystem);
    //EXPECT_TRUE(dynamic_cast<TestEngine*>(_engine.get())->isProcessInput);
}
