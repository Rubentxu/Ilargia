#include "core/MessageQueue.h"
#include <chrono>
#include <condition_variable>
#include <queue>
#include <map>
#include <mutex>
#include <utility>

namespace Ilargia {

    class Queue::Impl {
    public:
        Impl() : queue_(), queueMutex_(), queueCond_(), responseMap_(), responseMapMutex_() { }

        void put(Message &&msg) {
            {
                std::lock_guard<std::mutex> lock(queueMutex_);
                queue_.push(msg.move());
            }
            queueCond_.notify_one();
        }

        std::unique_ptr<Message> get(int timeoutMillis) {
            std::unique_lock<std::mutex> lock(queueMutex_);

            if (timeoutMillis <= 0)
                queueCond_.wait(lock, [this] { return !queue_.empty(); });
            else {
                auto timeoutOccured = !queueCond_.wait_for(
                        lock,
                        std::chrono::milliseconds(timeoutMillis),
                        [this] { return !queue_.empty(); });

                if (timeoutOccured)
                    queue_.emplace(new Message(MSG_TIMEOUT));
            }

            auto msg = queue_.front()->move();
            queue_.pop();
            return msg;
        }

        std::unique_ptr<Message> request(Message &&msg) {
            std::unique_lock<std::mutex> lock(responseMapMutex_);
            auto it = responseMap_.emplace(
                    std::make_pair(msg.getUniqueId(), std::unique_ptr<Queue>(new Queue))).first;
            lock.unlock();

            put(std::move(msg));
            auto response = it->second->get(); // Block until response is put to the response Queue

            lock.lock();
            responseMap_.erase(it); // Delete the response Queue
            lock.unlock();

            return response;
        }

        void respondTo(MsgUID reqUid, Message &&responseMsg) {
            std::lock_guard<std::mutex> lock(responseMapMutex_);
            if (responseMap_.count(reqUid) > 0)
                responseMap_[reqUid]->put(std::move(responseMsg));
        }

    private:

        std::queue<std::unique_ptr<Message>> queue_;

        std::mutex queueMutex_;

        std::condition_variable queueCond_;

        std::map<MsgUID, std::unique_ptr<Queue>> responseMap_;

        std::mutex responseMapMutex_;
    };

    Queue::Queue()
            : impl_(new Impl) {
    }

    Queue::~Queue() {
    }

    void Queue::put(Message &&msg) {
        impl_->put(std::move(msg));
    }

    std::unique_ptr<Message> Queue::get(int timeoutMillis) {
        return impl_->get(timeoutMillis);
    }

    std::unique_ptr<Message> Queue::request(Message &&msg) {
        return impl_->request(std::move(msg));
    }

    void Queue::respondTo(MsgUID reqUid, Message &&responseMsg) {
        impl_->respondTo(reqUid, std::move(responseMsg));
    }

}