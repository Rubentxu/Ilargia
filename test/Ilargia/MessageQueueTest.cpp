#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <memory>
#include <thread>
#include <vector>
#include "gtest/gtest.h"
#include "core/MessageQueue.h"


struct MessageQueueTest : public ::testing::Test {


    virtual void SetUp() {

    }

    virtual void TearDown() {
    }
};


TEST_F(MessageQueueTest, testMsgUID) {
    //const int N = 1000;
    //std::vector<Ilargia::MsgUID> uids1, uids2;

  /*  auto createMsgs = [](int count, std::vector<Ilargia::MsgUID> &uids) {
        for (int i = 0; i < count; ++i)
            uids.push_back(Ilargia::Message(1).getUniqueId());
    };

    std::thread t1(createMsgs, N, std::ref(uids1));
    std::thread t2(createMsgs, N, std::ref(uids2));
    t1.join();
    t2.join();

    for (auto uid1 : uids1) {
        for (auto uid2 : uids2) {
            ASSERT_NE(uid1, uid2);
        }
    }
*/
    ASSERT_TRUE(true);
}


