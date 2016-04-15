#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include "gtest/gtest.h"
#include "core/Game.h"
#include <chrono>
#include <thread>
#include <signal.h>
#include <unistd.h>


class ChronoTimer:  public Ilargia::Timer {
public:
    ChronoTimer(double step) : Timer(step) { }

    virtual double getSecondsTime() override  {
        return std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()/1000.0;
    }

};

struct TimerTest: public ::testing::Test {
    std::shared_ptr<Ilargia::Timer> _timer;


    virtual void SetUp() {
        _timer = std::make_shared<ChronoTimer>(60);
    }

    virtual void TearDown() {
    }

};


TEST_F(TimerTest, testStep) {
    _timer->start();
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(0,_timer->numStep());
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{16.7});
    ASSERT_DOUBLE_EQ(0.016666666666666666,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{16.7});
    ASSERT_DOUBLE_EQ(0.016666666666666666,_timer->step());
    EXPECT_EQ(2,_timer->numStep());
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(2,_timer->numStep());

}


TEST_F(TimerTest, testPause) {
    _timer->start();
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(0,_timer->numStep());
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{16.7});
    ASSERT_DOUBLE_EQ(0.016666666666666666,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    _timer->pause();
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{100});
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(1,_timer->numStep());
    _timer->unpause();
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>{16.7});
    ASSERT_DOUBLE_EQ(0.016666666666666666,_timer->step());
    EXPECT_EQ(2,_timer->numStep());
    ASSERT_DOUBLE_EQ(0.0,_timer->step());
    EXPECT_EQ(2,_timer->numStep());

}

volatile bool alarmed = false;

void alrm_handler(int) {
    alarmed = true;
}

TEST_F(TimerTest, testFrames) {
    _timer->start();
    signal(SIGALRM, alrm_handler);

    alarm(1);
    while(not alarmed){
        _timer->step();
    }
    EXPECT_EQ(60,_timer->numStep());


}
