#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include "gtest/gtest.h"
#include "core/Game.h"
#include <chrono>
#include <thread>


class ChronoTimer:  public Ilargia::Timer {
public:
    ChronoTimer(double step) : Timer(step) { }

    virtual double getTime() override  {
        return std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()/1000.0;
    }

};

struct TimerTest: public ::testing::Test {
    std::shared_ptr<Ilargia::Timer> _timer;


    virtual void SetUp() {
        _timer = std::make_shared<ChronoTimer>(0.2);
    }

    virtual void TearDown() {
    }

};


TEST_F(TimerTest, testStep) {
    _timer->Start();
    EXPECT_FALSE(_timer->tick());
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{200.0});
    EXPECT_TRUE(_timer->tick());
    //EXPECT_TRUE(dynamic_cast<TestEngine *>(_engine.get())->isInitSystem);

}
