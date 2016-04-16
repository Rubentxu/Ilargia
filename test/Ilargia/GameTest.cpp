#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <thread>
#include "gtest/gtest.h"
#include "core/Game.h"
#include "Commons.h"

struct GameTest : public ::testing::Test {
    std::shared_ptr<Ilargia::Engine> _engine;
    std::shared_ptr<Ilargia::Timer> _timer;
    std::shared_ptr<Ilargia::Game> _game;
    std::shared_ptr<Ilargia::GameState> _gameState;

    virtual void SetUp() {
        _timer = std::make_shared<TestTimer>();
        _engine = std::make_shared<TestEngine>(std::make_shared<TestManager>());
        _game = std::make_shared<Ilargia::Game>(_engine, _timer);
        _gameState = std::make_shared<TestGameState>(_engine);
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
    EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isShutdown);

}

TEST_F(GameTest, testPushState) {
    _game->pushState(_gameState);

    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isLoadResources);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isInit);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isOnResume);


}

TEST_F(GameTest, testPopState) {
    _game->pushState(_gameState);
    _game->changeState(_gameState);

    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isLoadResources);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isInit);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isOnResume);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isOnPause);
    EXPECT_TRUE(dynamic_cast<TestGameState *>(_gameState.get())->isUnloadResources);

}
